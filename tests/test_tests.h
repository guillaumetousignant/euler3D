#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestsTest : public CppUnit::TestFixture  {
private:
  int val1, val2, val3;
public:
  void setUp()
  {
    val1 = 1;
    val2 = 2;
    val3 = 3;  
  }

  void tearDown() 
  {
    // Destructor or whatever
  }

  void testEquality()
  {
    CPPUNIT_ASSERT(val1 == val1);
    CPPUNIT_ASSERT(!(val1 == val2));
  }

  void testAddition()
  {
    CPPUNIT_ASSERT(val1 + val2 == val3);
  }

  public: 
  static CppUnit::Test *suite()
  {
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("testsTest");
    suiteOfTests->addTest(new CppUnit::TestCaller<TestsTest>( 
                                   "testEquality", 
                                   &TestsTest::testEquality));
    suiteOfTests->addTest(new CppUnit::TestCaller<TestsTest>(
                                   "testAddition",
                                   &TestsTest::testAddition));
    return suiteOfTests;
  }  
};