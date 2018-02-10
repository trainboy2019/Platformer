#include <string>
#include <fstream>
#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include "json/json.h"
#include "main.h"
#include "player_png.h"

using namespace std;



int main() {
    aptInit();
    sf2d_init();
    sf2d_texture* player = sfil_load_PNG_buffer(player_png,        SF2D_PLACE_RAM);

	int posx = (320 / 2);
	int posy = (240 / 2);
    
    int playerX=0;
    int playerY=0;
    int color = 1;
    int style = 1;
    int rgb=0;
    bool pressed = false;
    
    
    vector<bool> bounce;
    vector<u32> color;
    vector<bool> solidTop;
    vector<bool> solidBottom;
    vector<bool> solidLeft;
    vector<bool> solidRight;
    vector<bool> isWater;
    vector<bool> gravity;
    vector<bool> death;
    vector<bool> goal;
    vector<int> toggles;
    vector<int> toggledBy;
    
    std::ifstream bifs("/3ds/Platformer/levels/level1blocks.json");
    Json::Reader breader;
    Json::Value bobj;
    if (bifs.is_open()) {
        bifs >> bobj;
    }
    breader.parse(bifs, bobj);
    for (int bindex=0;bindex<bobj.size();bindex++){
        string rawColor=bobj[to_string(bindex)]["color"].to_string();
        rawColor.erase(0,1);
        istringstream converter(rawColor);
        u32 useableColor;
        converter >> hex >> value;
        bounce.push_back(bobj[to_string(bindex)]["bounce"].asBool());
        solidTop.push_back(bobj[to_string(bindex)]["solidTop"].asBool());
        solidBottom.push_back(bobj[to_string(bindex)]["solidBottom"].asBool());
        solidLeft.push_back(bobj[to_string(bindex)]["solidLeft"].asBool());
        solidRight.push_back(bobj[to_string(bindex)]["solidRight"].asBool());
        isWater.push_back(bobj[to_string(bindex)]["isWater"].asBool());
        gravity.push_back(bobj[to_string(bindex)]["gravity"].asBool());
        death.push_back(bobj[to_string(bindex)]["death"].asBool());
        goal.push_back(bobj[to_string(bindex)]["goal"].asBool());
        color.push_back(useableColor);
        toggles.push_back(bobj[to_string(bindex)]["toggles"].asInt());
        toggledBy.push_back(bobj[to_string(bindex)]["toggledBy"].asString());
    }
    
    vector<vector<int>> allPos;
    std::ifstream ifs("/3ds/Platformer/levels/level1.json");
    Json::Reader reader;
    Json::Value obj;
    if (ifs.is_open()) {
        ifs >> obj;
    }
    reader.parse(ifs, obj);
    const Json::Value rows = obj[0];
    for (int index=0;index<rows.size();++index)
        for (int index2=0;index2<rows[index].size();index2++)
            for (int index3=0;index3<rows[index][index2].size();index3++){
                string data=rows[index][index2][index3].get(to_string(index3),-1).asString();
                stringstream convert(data);
                int kind;
                convert >> kind;
                vector<int> pos;
                pos.push_back(index3*8);
                pos.push_back(index*8);
                pos.push_back(index3*8+8);
                pos.push_back(index*8+8);
                pos.push_back(kind);
                allPos.push_back(pos);
            }
    
    
	// Main loop
	while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        u32 kHeld = hidKeysHeld();
        u32 kUp = hidKeysUp();
        
        
        
        if (kHeld & KEY_DUP) {
            if (color==8) {
                color=1;
            }
            else{
                color++;
            }
        }
        
        if (kHeld & KEY_DRIGHT) {
            if (style==4) {
                style=1;
            }
            else{
                style++;
            }
        }
        if (kHeld & KEY_DLEFT) {
            if (style==1) {
                style=4;
            }
            else{
                style--;
            }
        }
        
        
        
        
        
        
        if (kUp & KEY_DUP) {
            if (color==8) {
                color=1;
            }
            else{
                color++;
            }
        }
        
        if (kUp & KEY_DRIGHT) {
            if (style==4) {
                style=1;
            }
            else{
                style++;
            }
        }
        if (kUp & KEY_DLEFT) {
            if (style==1) {
                style=4;
            }
            else{
                style--;
            }
        }

		if (kDown & KEY_START) {
			break;
		}

        
        // draw instructions
        sf2d_start_frame(GFX_TOP, GFX_LEFT);
        for (int i=0;i<allPos.size();i++){
            sf2d_draw_rectangle(allPos[i][0],allPos[i][1],8,8,color[allPos[i][4]];
        }
        sf2d_end_frame();

		sf2d_swapbuffers();
	}
    

    sf2d_free_texture(player);

	sf2d_fini();

    
    aptExit();
	return 0;
}
