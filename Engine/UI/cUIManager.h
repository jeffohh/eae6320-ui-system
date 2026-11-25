#pragma once
#include "cUIElement.h"
#include "cUIFont.h"
#include <Engine/Results/Results.h>
#include <Engine/Graphics/cMesh.h>
#include <Engine/Graphics/cEffect.h>
#include <vector>
#include <memory>
#include <cstdint>

namespace eae6320
{
	namespace UI
	{
		class cUIManager
		{
		public:
			cResult Initialize();
			cResult CleanUp();

			// Element Management
			template<class tElement, class... tArguments>
			tElement* CreateElement(tArguments&&... i_arguments) {
				static_assert(std::is_base_of<cUIElement, tElement>::value, "cUIManager::CreateElement can only be used to add elements that inherit from cUIElement");
				auto element = std::make_unique<tElement>(std::forward<tArguments>(i_arguments)...);
				auto* const elementPtr = element.get();
				m_elements.push_back(std::move(element));
				return elementPtr;
			}
			void ClearElements();

			cUIFont& GetFont() { return m_font; }

			// Frame Loop
			void Update(float i_elapsedSecondCount);
			void Submit(uint16_t i_screenWidth, uint16_t i_screenHeight);

			cUIManager() = default;
			~cUIManager();

		private:
			std::vector<std::unique_ptr<cUIElement>> m_elements;

			// Shared UI Assets
			Graphics::cMesh* m_quadMesh = nullptr;
			Graphics::cEffect* m_uiEffect = nullptr;
			cUIFont m_font;

			cUIManager(const cUIManager&) = delete;
			cUIManager(cUIManager&&) = delete;
			cUIManager& operator=(const cUIManager&) = delete;
			cUIManager& operator=(cUIManager&&) = delete;
		};
	}
}

