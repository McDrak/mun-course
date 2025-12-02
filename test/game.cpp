#include "AssignmentOne/AssignmentOne.hpp"

int main()
{
	MunGame::AssignmentOne test("media/setupAssignmentOne.cfg");
	test.Init();
	test.Render();

	return 0;
}
