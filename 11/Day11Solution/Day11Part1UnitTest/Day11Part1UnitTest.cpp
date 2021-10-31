#include "pch.h"
#include "CppUnitTest.h"
#include "PanelGrid.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Day11Part1UnitTest
{
	TEST_CLASS(Day11Part1UnitTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{		
			PanelGrid testPanel{100,100,0};
			Assert::IsTrue(testPanel.getColor() == 0);
		}

		TEST_METHOD(TestMethod2)
		{
			PanelGrid testPanel{ 100,100,0 };
			testPanel.paintColor(1);
			Assert::IsTrue(testPanel.getColor() == 1);
		}

		TEST_METHOD(TestMethod3)
		{
			PanelGrid testPanel{ 100,100,0 };
			testPanel.paintColor(1);
			testPanel.paintColor(0);
			Assert::IsTrue(testPanel.getColor() == 0);
		}

	};
}
