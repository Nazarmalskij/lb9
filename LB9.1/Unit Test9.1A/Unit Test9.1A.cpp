#include "pch.h"
#include "CppUnitTest.h"
#include "D:\Project\Lb9\LB9.1\Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest91A
{
	TEST_CLASS(UnitTest91A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int c;
			int const i = 1;
			Students* S = new Students[];
			c = Find_Students(S, 2);
			Assert::AreEqual(c, 2);
		}
	};
}
