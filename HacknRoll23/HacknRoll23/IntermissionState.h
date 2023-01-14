#ifndef INTERMISSIONSTATE_H
#define INTERMISSIONSTATE_H

#include "imports.h"
#include "DEFINITIONS.h"

class IntermissionState :
		public State
	{
	private:
		Font font;
		RectangleShape background;

		float coolDown=.5f;
		float timer;
		int upgradePoints = 0;
		
		std::map<std::string, int> upgradeCur; //player's current upgrades
		std::map<std::string, int> upgradeIndex; //upgrade indexes
		std::map<std::string, Texture> upgradeTextures;
		std::map<std::string, Sprite> upgradeSprite;
		std::map<std::string, Text> upgradeDesc;
		//UI stuff
		RectangleShape fillBox;
		std::vector<RectangleShape> fillBoxes;//indicate upgraded skills
		std::map<std::string, std::vector<RectangleShape>> upgradeOutline;
		std::map<std::string, gui::Button*> upgradeBox; // + box

		Text title;
		Text text;

		gui::Button* nextBtn;
		RectangleShape btnBG;

		int waveNum;
		void initFont();
		void initVariables();
		void initGui();
		void resetGui();
	public:
		IntermissionState(StateData* state_data, std::map<std::string, int> upgradeCur, int waveNum);
		~IntermissionState();

		//Functions
		void update(const float& dt);
		void updateInput(const float& dt);
		void updateButtons();
		void render(RenderTarget* target = NULL);
	};
#endif

