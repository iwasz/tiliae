#include <clang/AST/ASTConsumer.h>
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendAction.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include <fstream>

using namespace clang;
using namespace clang::tooling;
using namespace clang::ast_matchers;
using namespace llvm;

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory ("tiliaeparser options");
static cl::opt<std::string> outputFilename ("o", cl::desc ("Specify output filename"), cl::value_desc ("filename"));

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static cl::extrahelp CommonHelp (CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static cl::extrahelp MoreHelp ("\nMore help text...");

std::ofstream outputFile;

//static const clang::FileEntry * getFileEntryForDecl(const clang::Decl * decl, clang::SourceManager * sourceManager)
//{
//    if (!decl || !sourceManager) {
//        return 0;
//    }
//    clang::SourceLocation sLoc = decl->getLocation();
//    clang::FileID fileID = sourceManager->getFileID(sLoc);
//    std::pair<FileID, unsigned> pair = sourceManager->getDecomposedIncludedLoc(fileID);
//    return sourceManager->getFileEntryForID(fileID);
//}

//static const char * getFileNameForDecl(const clang::Decl * decl, clang::SourceManager * sourceManager)
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
 * @brief The CXXRecordDeclStmtHandler class
 */
class CXXRecordDeclStmtHandler : public MatchFinder::MatchCallback {
    public:
        virtual void run (const MatchFinder::MatchResult &Result);
};

void CXXRecordDeclStmtHandler::run (const MatchFinder::MatchResult &Result)
{
        const CXXRecordDecl *decl = Result.Nodes.getNodeAs<CXXRecordDecl> ("cxxRecordDecl");
        ASTContext *context = Result.Context;

        /*---------------------------------------------------------------------------*/

        SourceManager const *sourceManager = &context->getSourceManager ();
        clang::SourceLocation sLoc = decl->getLocation ();
        clang::FileID fileID = sourceManager->getFileID (sLoc);
        //        const clang::FileEntry *fileEntry = sourceManager->getFileEntryForID (fileID);

        SourceLocation sl = sourceManager->getIncludeLoc (fileID);
        bool includedFromMain = sourceManager->isInMainFile (sl);

        if (!includedFromMain) {
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
        outputFile << "\t{\n";
        outputFile << "\t\tClass *clazz = new Class (\"" << className << "\", typeid (" << className << " &), new Reflection::PtrDeleter <" << className << ">);\n";
        outputFile << "\t\tManager::add (clazz);\n";

        /*---------------------------------------------------------------------------*/

        if (decl->hasDefaultConstructor ()) {
                outputFile << "\t\tclazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <" << className
                           << ", void>::Level1Wrapper::newConstructorPointer ()));\n";
        }

        for (CXXConstructorDecl const *constructor : decl->ctors ()) {

                if (constructor->isImplicit () || constructor->param_size () == 0) {
                        continue;
                }

                outputFile << "\t\tclazz->addConstructor (new Constructor (Reflection::ConstructorPointerWrapper2 <" << className << ", ";

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

        /*---------------------------------------------------------------------------*/

        for (const auto &field : decl->fields ()) {
                const StringRef &name = field->getName ();

                if (field->getAccess () != AS_public) {
                        continue;
                }

                SplitQualType T_split = field->getType ().split ();

                llvm::outs () << "    field : [" << QualType::getAsString (T_split) << "] [" << name << "]\n";
        }

        /*---------------------------------------------------------------------------*/

        for (CXXMethodDecl const *method : decl->methods ()) {
                if (method->isImplicit ()) {
                        continue;
                }

                IdentifierInfo const *identifier = method->getIdentifier ();

                if (identifier) {
//                        llvm::outs () << "    method : [" << identifier->getName () << " (";
                        outputFile << "\t\tclazz->addMethod (new Method (\"" << identifier->getName ().str()
                                   << "\", createMethodWrapper (&" << className << "::" << identifier->getName ().str() << ")));\n";
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
                Matcher.addMatcher (cxxRecordDecl (isDefinition ()).bind ("cxxRecordDecl"), &handlerForClasses);
        }

        virtual void HandleTranslationUnit (clang::ASTContext &Context)
        {
                //    Visitor.TraverseDecl(Context.getTranslationUnitDecl());
                Matcher.matchAST (Context);
        }

    private:
        //  FindNamedClassVisitor Visitor;
        CXXRecordDeclStmtHandler handlerForClasses;

        MatchFinder Matcher;
};

/**
 * @brief The FindNamedClassAction class
 */
class FindNamedClassAction : public clang::ASTFrontendAction {
    public:
        virtual std::unique_ptr<clang::ASTConsumer>
        CreateASTConsumer (clang::CompilerInstance &Compiler, llvm::StringRef InFile)
        {
                return std::unique_ptr<clang::ASTConsumer> (
                        new FindNamedClassConsumer (/*&Compiler.getASTContext()*/));
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

        outputFile << "#include <reflection/Reflection.h>\n";
        outputFile << "#include \"" << OptionsParser.getSourcePathList ().front () << "\"\n";
        outputFile << "\n";
        outputFile << "using namespace Core;\n";
        outputFile << "using namespace Reflection;\n";
        outputFile << "\n";
        outputFile << "void createReflectionDatabase__ ()\n";
        outputFile << "{\n";

        int ret = Tool.run (newFrontendActionFactory<FindNamedClassAction> ().get ());

        outputFile << "}" << std::endl;
        return ret;
}
