#include <iostream>
#include <string>
#include <list>
#include <cppunit/TestCase.h>
#include <cppunit/TestFixture.h>
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include <netinet/in.h>
#include <server.h>
using namespace CppUnit;
using namespace std;
 
//-----------------------------------------------------------------------------
class TestBasicServer : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestBasicServer);
    CPPUNIT_TEST(testreadFromNtpServer);
   // CPPUNIT_TEST(testMultiply);
    CPPUNIT_TEST_SUITE_END();
 
public:
    void setUp(void);
    void tearDown(void);
 
protected:
    void testreadFromNtpServer(void);
    //void testMultiply(void);
 
private:
    Server *mTestObj;
};
void TestBasicServer::testreadFromNtpServer(void)
{
    CPPUNIT_ASSERT(4 == mTestObj->readFromNtpServer());
}
//void TestBasicMath::testMultiply(void)
//{
//    CPPUNIT_ASSERT(6 == mTestObj->Multiply(2,3));
//}
void TestBasicServer::setUp(void)
{
    mTestObj = new Server(8088);
}
void TestBasicServer::tearDown(void)
{
    delete mTestObj;
}

//-----------------------------------------------------------------------------
CPPUNIT_TEST_SUITE_REGISTRATION( TestBasicServer );
int main(int argc, char* argv[])
{
    // informs test-listener about testresults
    CPPUNIT_NS::TestResult testresult;
    // register listener for collecting the test-results
    CPPUNIT_NS::TestResultCollector collectedresults;
    testresult.addListener (&collectedresults);
    // register listener for per-test progress output
    CPPUNIT_NS::BriefTestProgressListener progress;
    testresult.addListener (&progress);
    // insert test-suite at test-runner by registry
    CPPUNIT_NS::TestRunner testrunner;
    testrunner.addTest (CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest ());
    testrunner.run(testresult);
    // output results in compiler-format
    CPPUNIT_NS::CompilerOutputter compileroutputter(&collectedresults, std::cerr);
    compileroutputter.write ();
    // Output XML for Jenkins CPPunit plugin
    ofstream xmlFileOut("cppTestBasicMathResults.xml");
    XmlOutputter xmlOut(&collectedresults, xmlFileOut);
    xmlOut.write();
    // return 0 if tests were successful
    return collectedresults.wasSuccessful() ? 0 : 1;
}
