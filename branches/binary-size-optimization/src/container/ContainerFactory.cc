/****************************************************************************
 *                                                                          *
 *  Author : lukasz.iwaszkiewicz@gmail.com                                  *
 *  ~~~~~~~~                                                                *
 *  License : see COPYING file for details.                                 *
 *  ~~~~~~~~~                                                               *
 ****************************************************************************/

#include <iostream>
#include <Pointer.h>
#include <NoopEditor.h>

#include "metaStructure/model/MetaStructure.h"
#include "common/testHelpers/ContainerTestFactory.h"
#include "metaStructure/service/PrintService.h"
#include "metaStructure/service/MetaVisitor.h"
#include "metaStructure/service/ParentService.h"
#include "beanFactory/service/ValueServiceHelper.h"
#include "Defs.h"
#include "ContainerFactory.h"
#include "beanFactory/service/BeanFactoryService.h"
#include "beanFactory/service/BeanFactoryInitService.h"
#include "beanFactory/service/MappedValueService.h"
#include "beanFactory/service/IndexedValueService.h"
#include "beanFactory/service/FactoryService.h"
#include "beanFactory/service/BeanStackUpdateService.h"
#include "metaStructure/model/MetaObject.h"
#include "../beanWrapper/plugins/PropertyRWBeanWrapperPlugin.h"
#include "../beanWrapper/plugins/GetPutMethodRWBeanWrapperPlugin.h"
#include "../beanWrapper/plugins/MethodPlugin.h"
#include "../beanWrapper/plugins/ListPlugin.h"
#include "../beanWrapper/beanWrapper/BeanWrapper.h"
#include "../factory/ScalarFactory.h"
#include "../factory/ReflectionFactory.h"
#include "../factory/ChainFactory.h"
#include "../editor/TypeEditor.h"
#include "../editor/LexicalEditor.h"
#include "../editor/StringConstructorEditor.h"
#include "../editor/ChainEditor.h"
#include "../core/DebugContext.h"
#include "beanFactory/BeanFactoryContext.h"
#include "../editor/StreamEditor.h"
#include "../editor/StringFactoryMethodEditor.h"
#include "beanFactory/service/EditorService.h"
#include "variant/PtrDeleter.h"

using Editor::StringFactoryMethodEditor;

//#define CONTAINER_PRINT_META 1

namespace Container {
using namespace Wrapper;

/****************************************************************************/

void ContainerFactory::init (BeanFactoryContainer *bfCont, MetaContainer *metaCont)
{
        MetaVisitor iteration0; // TODO testowa, w celu naprawienia błędu z parentowaniem.
        MetaVisitor iteration1;
        MetaVisitor iteration2;
        BeanFactoryContext ctx;
        BeanFactoryVisitorContext context;
        Core::VariantMap *singletons = bfCont->getSingletons ();

        try {

                iteration0.setContext (&context);

                ParentService parentService;
                parentService.setContext (&context);
                iteration0.addService (&parentService);

/*------1st-iteration-------------------------------------------------------*/

                iteration1.setContext (&context);

//                Ptr <IMetaService> service = ParentService::create ();
//                service->setContext (&context);
//                iteration1.addService (service);

                BeanFactoryInitService bfService;
                bfService.setContext (&context);
                bfService.setDefaultBeanWrapper (vcast <BeanWrapper *> (singletons->operator[] (BEAN_WRAPPER_W_CONVERSION)));
                iteration1.addService (&bfService);

                MappedValueService valMapService;
                valMapService.setContext (&context);
                ValueServiceHelper helper;
                helper.setSingletonMap (singletons);
                valMapService.setValueServiceHelper (&helper);
                iteration1.addService (&valMapService);

                IndexedValueService valIndexService;
                valIndexService.setContext (&context);
                helper.setSingletonMap (singletons);
                valIndexService.setValueServiceHelper (&helper);
                iteration1.addService (&valIndexService);

/*------2nd-iteration-------------------------------------------------------*/

                iteration2.setContext (&context);

                BeanStackUpdateService updService;
                updService.setContext (&context);
                iteration2.addService (&updService);

                EditorService editorService;
                editorService.setContext (&context);
                editorService.init (singletons);
                iteration2.addService (&editorService);

                FactoryService factoryService;
                factoryService.setContext (&context);
                factoryService.init (singletons);
                iteration2.addService (&factoryService);

#if CONTAINER_PRINT_META
                Ptr <PrintMetaService> printService = PrintMetaService::create ();
                printService->setContext (&context);
                iteration2.addService (printService);
#endif

                context.reset ();
                context.setBeanFactoryContainer (bfCont);
                context.setBeanFactoryMap (&bfCont->getBeanFactoryMap ());
                metaCont->accept (&iteration0);
                metaCont->accept (&iteration1);
                metaCont->accept (&iteration2);

/*------2.5-iteration-*global*-singletons-----------------------------------*/

                // Tworzymy singletony (ale tylko te globalne). Czyli nie iterujemy przez wszystko, a
                BeanFactoryMap *beanFactoryMap = context.getBeanFactoryMap ();
                for (BeanFactoryMap::nth_index <1>::type::iterator i = beanFactoryMap->get<1> ().begin ();
                     i  != beanFactoryMap->get<1> (). end ();
                     ++i) {

                        Ptr <BeanFactory> factory = *i;

                        bool isSingleton = (static_cast <MetaObject::Scope> (factory->getIntAttribute (Attributes::SCOPE_ARGUMENT)) == MetaObject::SINGLETON);
                        bool isLazyInit = factory->getBoolAttribute (Attributes::LAZYINIT_ARGUMENT);

                        if (isSingleton && !isLazyInit) {
                                Core::Variant v = factory->create (Core::VariantMap (), &ctx);

                                if (v.isNone ()) {
                                        throw ContainerException (ctx, "ContainerFactory::fill : error creating singleton [" + (*i)->getId () + "].");
                                }
                        }
                }
        }
        catch (NoSuchBeanException &e) {
                e.addMessage ("ContainerFactory::createContainer : [" + bfCont->toString () + "].");
                throw;
        }
        catch (Core::Exception &e) {
                e.addMessage ("ContainerFactory::createContainer : [" + bfCont->toString () + "].");
                throw;
        }
}

/****************************************************************************/

Ptr <BeanFactoryContainer> ContainerFactory::create (Ptr <MetaContainer> metaCont,
                                                     bool storeMetaContainer,
                                                     BeanFactoryContainer *linkedParent)
{
//        Core::IAllocator *allocator = new Core::RegionAllocator ();
        Ptr <BeanFactoryContainer> container = boost::make_shared <BeanFactoryContainer> (createSingletons ());

        if (linkedParent) {
                container->setLinked (linkedParent);
                metaCont->setLinked (linkedParent->getMetaContainer ());
        }

        if (storeMetaContainer) {
                container->setMetaContainer (metaCont);
        }

        return container;
}


/****************************************************************************/

Ptr <BeanFactoryContainer> ContainerFactory::createAndInit (Ptr <MetaContainer> metaCont,
                                                            bool storeMetaContainer,
                                                            BeanFactoryContainer *linkedParent)
{
        Ptr <BeanFactoryContainer> container = create (metaCont, storeMetaContainer,linkedParent);
        init (container.get (), metaCont.get ());
        return container;
}

/****************************************************************************/

Core::VariantMap *ContainerFactory::createSingletons ()
{
        Core::VariantMap *map = new Core::VariantMap ();
        Editor::IEditor *noop = new Editor::NoopEditor ();


        map->operator[] (DEFAULT_MAPPED_EDITOR_NAME) = Core::Variant (noop);
//        map->operator[] (DEFAULT_MAPPED_EDITOR_NAME).setDeleter (new Core::PtrDeleter <Editor::NoopEditor>);

        map->operator[] (DEFAULT_INDEXED_EDITOR_NAME) = Core::Variant (noop);
        map->operator[] (NOOP_EDITOR_NAME) = Core::Variant (noop);
        map->operator[] (NOOP_NO_COPY_EDITOR_NAME) = Core::Variant (new Editor::NoopEditor (false));

        // Dodaj reflection factory.
        Factory::ScalarFactory *factS = new Factory::ScalarFactory ();
        Factory::ReflectionFactory *factR = new Factory::ReflectionFactory ();
        Factory::ChainFactory *fact = new Factory::ChainFactory (true);
        fact->addFactory (factS);
        fact->addFactory (factR);

        map->operator[] (DEFAULT_SINGLETON_FACTORY_NAME) = Core::Variant (fact);
        map->operator[] (DEFAULT_VALUE_FACTORY_NAME) = Core::Variant (factS);
        map->operator[] (BEAN_WRAPPER_SIMPLE) = Core::Variant (Wrapper::BeanWrapper::create ());

        BeanWrapper *beanWrapper = new BeanWrapper (true);
        beanWrapper->addPlugin (new PropertyRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new GetPutMethodRWBeanWrapperPlugin ());
        beanWrapper->addPlugin (new MethodPlugin (MethodPlugin::IMMEDIATE_CALL));

/*--------------------------------------------------------------------------*/

        Editor::TypeEditor *typeEditor = new Editor::TypeEditor (true);
        typeEditor->setEqType (new Editor::NoopEditor ());
        typeEditor->setNullType (new Editor::NoopEditor ());

        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (int), new Editor::StreamEditor <std::string, int> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (double), new Editor::LexicalEditor <std::string, double> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (float), new Editor::LexicalEditor <std::string, float> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (char), new Editor::LexicalEditor <std::string, char> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (bool), new Editor::LexicalEditor <std::string, bool> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (unsigned int), new Editor::StreamEditor <std::string, unsigned int> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (unsigned char), new Editor::StreamEditor <std::string, unsigned char> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (long), new Editor::StreamEditor <std::string, long> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (unsigned long), new Editor::StreamEditor <std::string, unsigned long> ()));

        // Core::String <-> std::string
        typeEditor->addType (Editor::TypeEditor::Type (typeid (Core::String), typeid (std::string), new Editor::LexicalEditor <Core::String, std::string> ()));
        typeEditor->addType (Editor::TypeEditor::Type (typeid (std::string), typeid (Core::String), new Editor::LexicalEditor <std::string, Core::String> ()));

        // StringCon.
        Editor::StringConstructorEditor *strCon = new Editor::StringConstructorEditor ();
        Editor::StringFactoryMethodEditor *conversionMethodEditor = new Editor::StringFactoryMethodEditor ();
        Editor::ChainEditor *chain = new Editor::ChainEditor;

        chain->addEditor (typeEditor);
        chain->addEditor (strCon);
        chain->addEditor (conversionMethodEditor);
        chain->addEditor (noop);

        beanWrapper->setEditor (chain);

/*--------------------------------------------------------------------------*/

        map->operator[] (BEAN_WRAPPER_W_CONVERSION) = Core::Variant (beanWrapper);
        map->operator[] (MAIN_TYPE_EDITOR) = Core::Variant (typeEditor);
        map->operator[] (MAIN_METHOD_CONVERSION_EDITOR) = Core::Variant (conversionMethodEditor);
        map->operator[] ("deleteMe1") = Core::Variant (strCon);

        return map;
}

}
