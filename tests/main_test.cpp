#include <cppunit/ui/text/TestRunner.h>
#include "test_tests.h"

int main( int argc, char **argv)
{
  CppUnit::TextUi::TestRunner runner;
  //runner.addTest( ExampleTestCase::suite() );
  runner.addTest(TestsTest::suite());
  bool wasSuccessful = runner.run( "", false );
  return !wasSuccessful;
}