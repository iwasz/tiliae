/**
 * Limitations :
 * - Namespace information is discarded. this means that class names must be unique in reflection manager.
 *
 * TODOs :
 * - Add more control, like reflect_whole class (+ no_reflect on its member for fine grained controll), and reflect_only_explicitly_annotated.
 */

#include <clang/AST/ASTConsumer.h>
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/AST/Comment.h"
#include <fstream>
#include <utility>

const char *TILIAE_REFLECT_ANNOTATION_STRING = "__tiliae_reflect__";
const char *TILIAE_REFLECT_TOKEN_ANNOTATION_STRING = "__tiliae_reflect_token__";
const char *TILIAE_NO_REFLECT_ANNOTATION_STRING = "__tiliae_no_reflect__";

using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory ("tiliaeparser options");
static cl::opt<std::string> outputFilename ("o", cl::desc ("Specify output filename"), cl::value_desc ("filename"));
static cl::opt<std::string> functionSuffix ("s", cl::desc ("Specify generated function suffix"), cl::value_desc ("function suffix"));

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp (CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp ("\nMore help text...");

std::ofstream outputFile;

// static const clang::FileEntry * getFileEntryForDecl(const clang::Decl * decl, clang::SourceManager * sourceManager)
//{
//    if (!decl || !sourceManager) {
//        return 0;
//    }
//    clang::SourceLocation sLoc = decl->getLocation();
//    clang::FileID fileID = sourceManager->getFileID(sLoc);
//    std::pair<FileID, unsigned> pair = sourceManager->getDecomposedIncludedLoc(fileID);
//    return sourceManager->getFileEntryForID(fileID);
//}

// static const char * getFileNameForDecl(const clang::Decl * decl, clang::SourceManager * sourceManager)
//{
//    const clang::FileEntry * fileEntry = getFileEntryForDecl(decl, sourceManager);
//    if (!fileEntry) {
//        return 0;
//    }
//    return fileEntry->getName();
//}

// class FindNamedClassVisitor
//    : public RecursiveASTVisitor<FindNamedClassVisitor> {
// public:
//  explicit FindNamedClassVisitor(ASTContext *Context) : Context(Context) {}

//  bool VisitCXXRecordDecl(CXXRecordDecl *Declaration) {
//    if (Declaration->getQualifiedNameAsString() == "n::m::C") {
//      FullSourceLoc FullLocation =
//          Context->getFullLoc(Declaration->getLocStart());
//      if (FullLocation.isValid())
//        llvm::outs() << "Found declaration at "
//                     << FullLocation.getSpellingLineNumber() << ":"
//                     << FullLocation.getSpellingColumnNumber() << "\n";
//    }
//    return true;
//  }

// private:
//  ASTContext *Context;
//};

/**
 * @brief Checks if tehre is an AnnotateAttr in attrRange, and if it's getText() equals to name.
 * @param attrRange
 * @param name
 * @return if it has annotation with given name and secdond annotation's name if there is any.
 * TODO Refactor
 */
static std::pair<bool, std::string> hasAnnotation (clang::Decl::attr_range const &attrRange, std::string const &name)
{
        bool annotationFound = false;
        std::string secondName;

        for (Attr const *attr : attrRange) {
                if (attr->getKind () != clang::attr::Annotate) {
                        continue;
                }

                AnnotateAttr const *annoAttr = static_cast<AnnotateAttr const *> (attr);

                if (annoAttr->getAnnotation ().str () == name) {
                        annotationFound = true;
                }
                else if (secondName.empty ()) {
                        secondName = annoAttr->getAnnotation ().str ();
                }

                if (annotationFound && !secondName.empty ()) {
                        break;
                }
        }

        return std::make_pair (annotationFound, secondName);
}

/**
 * @brief The CXXRecordDeclStmtHandler class
 */
class CXXRecordDeclStmtHandler : public MatchFinder::MatchCallback {
public:
        virtual void run (const MatchFinder::MatchResult &result);
};

void CXXRecordDeclStmtHandler::run (const MatchFinder::MatchResult &Result)
{
        const CXXRecordDecl *decl = Result.Nodes.getNodeAs<CXXRecordDecl> ("cxxRecordDecl");
        //        ASTContext *context = Result.Context;

        /*---------------------------------------------------------------------------*/

        //        SourceManager const *sourceManager = &context->getSourceManager ();
        //        clang::SourceLocation sLoc = decl->getLocation ();
        //        clang::FileID fileID = sourceManager->getFileID (sLoc);
        //        SourceLocation sl = sourceManager->getIncludeLoc (fileID);
        //        bool includedFromMain = sourceManager->isInMainFile (sl);

        /*
         * TODO tak nie działa :D Inclusion guards wycinają klasy z głównego pliku.
         * jeśli były one includowane w innym hederze włączonym do głownego pliku
         */
        //        if (!includedFromMain) {
        //                return;
        //        }

        auto tiliaeReflectioAnnotation = hasAnnotation (decl->attrs (), TILIAE_REFLECT_ANNOTATION_STRING);
        auto tiliaeReflectioTokenAnnotation = hasAnnotation (decl->attrs (), TILIAE_REFLECT_TOKEN_ANNOTATION_STRING);

        if (!tiliaeReflectioAnnotation.first && !tiliaeReflectioTokenAnnotation.first) {
                return;
        }

        //        llvm::outs () << decl->getName ();
        //        if (fileEntry && fileEntry->getName ()) {
        //                llvm::outs () << ", file [" << fileEntry->getName () << "]";
        //        }

        //        std::pair<FileID, unsigned> pair = sourceManager->getDecomposedIncludedLoc (fileID);
        //        fileEntry = sourceManager->getFileEntryForID (pair.first);

        //        if (fileEntry && fileEntry->getName ()) {
        //                llvm::outs () << ", xx [" << fileEntry->getName () << "], uu = " << pair.second << ", incFrmMain : " << includedFromMain;
        //        }

        /*---------------------------------------------------------------------------*/

        //        llvm::outs () << "\n";

        std::string className = decl->getName ();

        if (tiliaeReflectioTokenAnnotation.first) {
                className = tiliaeReflectioTokenAnnotation.second;
        }

        //        Type const *classType = decl->getTypeForDecl ();
        //        SplitQualType tSplit = qt.split ();
        //        outputFile << "\t\tclazz->addBaseClassName (\"" << QualType::getAsString (tSplit) << "\");\n";
        //        std::string fullName = QualType::getAsString (classType, Qualifiers ());
        std::string fullName = decl->getQualifiedNameAsString ();

        //        llvm::outs () << fullName << "\n";
        //        return;

        outputFile << "\t{\n";
        outputFile << "\t\tClass *clazz = new Class (\"" << className << "\", typeid (" << fullName << " &), new Reflection::PtrDeleter <" << fullName
                   << ">);\n";
        outputFile << "\t\tif (!Manager::add (clazz)) {\n\t\t\tdelete clazz;\n\t\t}\n\t\telse {\n";

        /*---------------------------------------------------------------------------*/

        for (CXXBaseSpecifier const &bse : decl->bases ()) {
                QualType qt = bse.getType ();
                outputFile << "\t\t\tclazz->addBaseClassName (\"" << qt->getAsCXXRecordDecl ()->getName ().str () << "\");\n";
        }

        if (!decl->isAbstract ()) {
                // Looks like implicit default constructor is not returned in decl->ctors () !?
                if (decl->hasDefaultConstructor () && !decl->hasUserProvidedDefaultConstructor ()) {
                        outputFile << "\t\t\tclazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <" << fullName
                                   << ", void>::Level1Wrapper::newConstructorPointer ()));\n";
                }

                for (CXXConstructorDecl const *constructor : decl->ctors ()) {

//                        if (className == "Country") {
//                                llvm::outs () << "Constructor! hasDef = [" << decl->hasDefaultConstructor () << "], isDef = ["
//                                              << constructor->isDefaultConstructor () << "], accessPub = [" << (constructor->getAccess () == AS_public)
//                                              << "], isImplicit = [" << constructor->isImplicit () << "], params0 = [" << (constructor->param_size () == 0)
//                                              << "]\n";
//                        }

                        if (decl->hasDefaultConstructor () && constructor->isDefaultConstructor () && constructor->getAccess () == AS_public) {
                                outputFile << "\t\t\tclazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <" << fullName
                                           << ", void>::Level1Wrapper::newConstructorPointer ()));\n";
                        }

                        if (constructor->isImplicit () || constructor->param_size () == 0 || constructor->getAccess () != AS_public) {
                                continue;
                        }

                        outputFile << "\t\t\tclazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <" << fullName << ", ";

                        for (clang::FunctionDecl::param_const_iterator i = constructor->param_begin (); i != constructor->param_end ();) {
                                SplitQualType tSplit = (*i)->getType ().split ();
                                outputFile << QualType::getAsString (tSplit);

                                if (++i == constructor->param_end ()) {
                                        break;
                                }
                                else {
                                        outputFile << ", ";
                                }
                        }

                        outputFile << ">::Level1Wrapper::newConstructorPointer ()));\n";
                }
        }

        /*---------------------------------------------------------------------------*/

        for (const FieldDecl *field : decl->fields ()) {
                const StringRef &name = field->getName ();
                QualType qType = field->getType ();

                if (field->getAccess () != AS_public || qType.isConstQualified ()) {
                        continue;
                }

                // SplitQualType tSplit = field->getType ().split ();
                outputFile << "\t\t\tclazz->addField (new Field (\"" << name.str () << "\", Reflection::createFieldWrapper (&" << fullName
                           << "::" << name.str () << ")));\n";
        }

        /*---------------------------------------------------------------------------*/

        for (CXXMethodDecl const *method : decl->methods ()) {

                if (method->isImplicit () || method->getAccess () != AS_public || hasAnnotation (method->attrs (), TILIAE_NO_REFLECT_ANNOTATION_STRING).first
                    || method->isStatic ()) {
                        continue;
                }

                IdentifierInfo const *identifier = method->getIdentifier ();

                if (identifier) {
                        //                        llvm::outs () << "    method : [" << identifier->getName () << " (";
                        outputFile << "\t\t\tclazz->addMethod (new Method (\"" << identifier->getName ().str () << "\", createMethodWrapper (&" << fullName
                                   << "::" << identifier->getName ().str () << ")));\n";
                }
                else {
                        continue;
                }

                //                for (ParmVarDecl const *param : method->parameters ()) {
                //                        SplitQualType T_split = param->getType ().split ();
                //                        llvm::outs () << QualType::getAsString (T_split) << ",";
                //                }

                //                llvm::outs () << ")\n";
        }

        //    decl->get

        //          Rewrite.InsertText(IncVar->getLocStart(), "/* increment */",
        //          true, true);
        outputFile << "\t\t}\n";
        outputFile << "\t}\n";
}

class CXXTypedefStmtHandler : public MatchFinder::MatchCallback {
public:
        virtual void run (const MatchFinder::MatchResult &Result);
};

void CXXTypedefStmtHandler::run (const MatchFinder::MatchResult &result)
{
        const TypedefDecl *decl = result.Nodes.getNodeAs<TypedefDecl> ("cxxTypedefDecl");
        std::string typedefName = decl->getName ();
        std::string typedefQualifiedName = decl->getQualifiedNameAsString ();

        outputFile << "\t{\n";
        outputFile << "\t\tClass *clazz = new Class (\"" << typedefName << "\", typeid (" << typedefQualifiedName << "&), new PtrDeleter <"
                   << typedefQualifiedName << " >);\n";
        outputFile << "\t\tif (!Manager::add (clazz)) {;\n";
        outputFile << "\t\t\tdelete clazz;\n";
        outputFile << "\t\t}\n\t\telse { \n";
        outputFile << "\t\t\tIConstructorPointer *cp = Reflection::ConstructorPointerWrapper2 <" << typedefQualifiedName
                   << ", void>::Level1Wrapper::newConstructorPointer ();\n";
        outputFile << "\t\t\tclazz->addConstructor (new Constructor (cp));\n\n";
        outputFile << "\t\t\tICallableWrapper *w = new AddWrapper <" << typedefQualifiedName << " > ();\n";
        outputFile << "\t\t\tclazz->addMethod (new Method (\"add\", w));\n\n";
        outputFile << "\t\t\tw = new GetWrapper <" << typedefQualifiedName << " > ();\n";
        outputFile << "\t\t\tclazz->addMethod (new Method (\"get\", w));\n\n";
        outputFile << "\t\t\tw = new SetWrapper <" << typedefQualifiedName << " > ();\n";
        outputFile << "\t\t\tclazz->addMethod (new Method (\"set\", w));\n\n";
        outputFile << "\t\t\tw = new IteratorWrapper <" << typedefQualifiedName << " > ();\n";
        outputFile << "\t\t\tclazz->addMethod (new Method (\"iterator\", w));\n";
        outputFile << "\t\t}\n";
        outputFile << "\t}\n";
}

/**
 * @brief The FindNamedClassConsumer class
 */
class FindNamedClassConsumer : public clang::ASTConsumer {
public:
        explicit FindNamedClassConsumer (/*ASTContext *Context*/) /*: Visitor(Context)*/
        {
                //                Matcher.addMatcher(cxxRecordDecl (isDefinition (), matchesName ("A.*")).bind("cxxRecordDecl"), &handlerForClasses);
                Matcher.addMatcher (recordDecl (isDefinition (), hasAttr (clang::attr::Annotate)).bind ("cxxRecordDecl"), &handlerForClasses);
                //                Matcher.addMatcher (typedefDecl (isDefinition (), hasAttr (clang::attr::Annotate)).bind ("cxxRecordDecl"),
                //                &handlerForTypedefs);
                Matcher.addMatcher (typedefDecl (hasAttr (clang::attr::Annotate)).bind ("cxxTypedefDecl"), &handlerForTypedefs);
        }

        virtual void HandleTranslationUnit (clang::ASTContext &Context)
        {
                //    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
                Matcher.matchAST (Context);
        }

private:
        //  FindNamedClassVisitor Visitor;
        CXXRecordDeclStmtHandler handlerForClasses;
        CXXTypedefStmtHandler handlerForTypedefs;
        MatchFinder Matcher;
};

/**
 * @brief The FindNamedClassAction class
 */
class FindNamedClassAction : public clang::ASTFrontendAction {
public:
        virtual std::unique_ptr<clang::ASTConsumer> CreateASTConsumer (clang::CompilerInstance &Compiler, llvm::StringRef InFile)
        {
                return std::unique_ptr<clang::ASTConsumer> (new FindNamedClassConsumer (/*&Compiler.getASTContext()*/));
        }
};

/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main (int argc, const char **argv)
{
        CommonOptionsParser OptionsParser (argc, argv, MyToolCategory);
        ClangTool Tool (OptionsParser.getCompilations (), OptionsParser.getSourcePathList ());
        outputFile.open (outputFilename);

        // clang-format off
        outputFile <<
R"(/*
 * This file was aut-generated by tiliaeparser. Do not modify. Unless.
 * Include only once.
 * https://github.com/iwasz/tiliae
 */

)";
/* clang-format on */

        outputFile << "#include <reflection/Reflection.h>\n";
        outputFile << "#include \"" << OptionsParser.getSourcePathList ().front () << "\"\n";
        outputFile << "\n";
        outputFile << "namespace {\n";
        outputFile << "using namespace Core;\n";
        outputFile << "using namespace Reflection;\n";
        outputFile << "\n";
        outputFile << "void createReflectionDatabase_" << functionSuffix << " ()\n";
        outputFile << "{\n";

        int ret = Tool.run (newFrontendActionFactory<FindNamedClassAction> ().get ());

        outputFile << "}\n";
        outputFile << "\n";

        outputFile << "struct Sentinel_" << functionSuffix << " {\n";
        outputFile << "        Sentinel_" << functionSuffix << " ()\n";
        outputFile << "        {\n";
        outputFile << "                createReflectionDatabase_" << functionSuffix << " ();\n";
        outputFile << "        }\n";
        outputFile << "};\n";
        outputFile << "\n";
        outputFile << "static Sentinel_" << functionSuffix << " sentinel_" << functionSuffix << ";\n";
        outputFile << "} // namespace\n" << std::endl;
        return ret;
}
