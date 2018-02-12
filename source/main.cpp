#include <string>
#include <fstream>
#include <3ds.h>
#include <sf2d.h>
#include <sfil.h>
#include "json/json.h"
#include "number0_png.h"
#include "number1_png.h"

using namespace std;



int main() {
    aptInit();
    sf2d_init();
    
    sf2d_texture* number0 = sfil_load_PNG_buffer(number0_png,        SF2D_PLACE_RAM);
    sf2d_texture* number1 = sfil_load_PNG_buffer(number1_png,        SF2D_PLACE_RAM);
    
    int playerX=0;
    int playerY=0;
    int playerIndex=-1;
    
    bool levelLoaded=false;
    bool levelBlockLoaded=false;
    
    
    vector<bool> bounce;
    vector<int> red;
    vector<int> green;
    vector<int> blue;
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
    vector<bool> isStart;
    
    std::ifstream bifs("/3ds/Platformer/levels/level1blocks.json");
    Json::Reader breader;
    Json::Value bobj;
    if (bifs.is_open()) {
        bifs >> bobj;
        levelBlockLoaded=true;
    }
    breader.parse(bifs, bobj);
    for (int bindex=0;bindex<bobj.size();bindex++){
        bounce.push_back(bobj[to_string(bindex)]["bounce"].asBool());
        solidTop.push_back(bobj[to_string(bindex)]["solidTop"].asBool());
        solidBottom.push_back(bobj[to_string(bindex)]["solidBottom"].asBool());
        solidLeft.push_back(bobj[to_string(bindex)]["solidLeft"].asBool());
        solidRight.push_back(bobj[to_string(bindex)]["solidRight"].asBool());
        isWater.push_back(bobj[to_string(bindex)]["isWater"].asBool());
        gravity.push_back(bobj[to_string(bindex)]["gravity"].asBool());
        death.push_back(bobj[to_string(bindex)]["death"].asBool());
        goal.push_back(bobj[to_string(bindex)]["goal"].asBool());
        red.push_back(bobj[to_string(bindex)]["color"]["r"].asInt());
        green.push_back(bobj[to_string(bindex)]["color"]["g"].asInt());
        blue.push_back(bobj[to_string(bindex)]["color"]["b"].asInt());
        toggles.push_back(bobj[to_string(bindex)]["toggles"].asInt());
        toggledBy.push_back(bobj[to_string(bindex)]["toggledBy"].asInt());
        isStart.push_back(bobj[to_string(bindex)]["isPlayer"].asBool());
    }
    
    vector<vector<int>> allPos;
    std::ifstream ifs("/3ds/Platformer/levels/level1.json");
    Json::Reader reader;
    Json::Value obj;
    if (ifs.is_open()) {
        ifs >> obj;
        levelLoaded=true;
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
    
    // draw instructions
    sf2d_start_frame(GFX_TOP, GFX_LEFT);
    for (int i=0;i<allPos.size();i++){
        if (isStart[allPos[i][4]]==false) {
            sf2d_draw_rectangle(allPos[i][0],allPos[i][1],8,8,RGBA8(red[allPos[i][4]],green[allPos[i][4]],blue[allPos[i][4]],255));
        }
        else{
            playerIndex=i;
            playerX=allPos[i][0]+4;
            playerY=allPos[i][1]+4;
            sf2d_draw_fill_circle(playerX,playerY,4,RGBA8(red[allPos[i][4]],green[allPos[i][4]],blue[allPos[i][4]],255));
        }
    }
    sf2d_end_frame();
    
    
	// Main loop
	while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();
        u32 kHeld = hidKeysHeld();
        u32 kUp = hidKeysUp();
        
        if (kHeld & KEY_DUP) {
            
        }
        
        if (kDown & KEY_DRIGHT) {
            if (playerX>=10&&playerX<=390) {
                playerX--;
                sf2d_draw_fill_circle(playerX,playerY,4,RGBA8(red[allPos[playerIndex][4]],green[allPos[playerIndex][4]],blue[allPos[playerIndex][4]],255));
            }
            
        }
        
        if (kDown & KEY_DLEFT) {
            if (playerX>=10&&playerX<=390) {
                playerX++;
                sf2d_draw_fill_circle(playerX,playerY,4,RGBA8(red[allPos[playerIndex][4]],green[allPos[playerIndex][4]],blue[allPos[playerIndex][4]],255));
            }
            
        }
        
		if (kDown & KEY_START) {
			break;
		}
        
        sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
        if (levelBlockLoaded) {
            sf2d_draw_texture(number1, 116, 0);
        }
        else
            sf2d_draw_texture(number0, 116, 0);
            
        if (levelLoaded) {
            sf2d_draw_texture(number1, 58, 0);
        }
        else
            sf2d_draw_texture(number0, 58, 0);
            
        sf2d_end_frame();

		sf2d_swapbuffers();
	}
    


	sf2d_fini();

    
    aptExit();
	return 0;
}
