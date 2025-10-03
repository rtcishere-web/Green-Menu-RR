#include "Render.h"
#include "Vars.h"

bool Render::isOpened = false;

bool Render::IsOpened() {
	return isOpened;
}

void Render::KeyManager() {
	if (GetAsyncKeyState(VK_INSERT) & 1 || GetAsyncKeyState(VK_DELETE) & 1) {
		isOpened = !isOpened;
		ImGui::GetIO().MouseDrawCursor = isOpened;
	}
}

void Render::UI() {

	if (isOpened)
	{
		Extra();

		ImGui::Begin("Template!");
		ImGui::SeparatorText("Random Text Separator!");
		ImGui::TextUnformatted("Hello World!");
		ImGui::Custom::FancyToggle("Fancy Toggle", &exampleToggle);
		ImGui::End();

		ImGui::Begin("Template Tab Bar!");

		if (ImGui::BeginTabBar("Tempate Menu"))
		{
			if (ImGui::BeginTabItem("Tab One")) {
				ImGui::TextUnformatted("Hello Tab One!");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Tab Two")) {
				ImGui::TextUnformatted("Hello Tab Two");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Credits")) {
				ImGui::TextUnformatted("Right Credits Here!");
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::End();
	}
}

void Render::Extra() {
	if (exampleToggle) {
		ImGui::Begin("Example Extra Window");
		ImGui::TextUnformatted("Hello Extra Window!");
		ImGui::End();
	}
}
