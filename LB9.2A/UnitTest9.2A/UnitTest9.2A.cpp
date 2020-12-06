#include "pch.h"
#include "CppUnitTest.h"
#include "../Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92A
{
	TEST_CLASS(UnitTest92A)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int* c;
			int const i = 1;
			Students* S = new Students[1];
			c = Index_sort(S, 1);
			Assert::AreEqual(*c, 0);
		}
	};
}
