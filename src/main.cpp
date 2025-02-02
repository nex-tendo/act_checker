#include <3ds.h>
#include <stdio.h>
#include <string.h>
#include "frda.h"

const char* get_account_url() {
    NASType serverType;
    NASEnvironment serverEnv;
    u8 serverEnvNum;
    
    frdaInit();
    
    Result rc = FRDA_GetServerTypes(&serverType, &serverEnv, &serverEnvNum);
    
    frdaExit();
    
    if (R_SUCCEEDED(rc) && serverType == 0x0) {
        return "https://account.nintendo.net/v1/api/";
    } else {
        return "http://account.nextendo.online/v1/api/";
    }
}

int main() {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    
    const char* account_url = get_account_url();
    printf("Account URL set to: %s\n", account_url);
    
    printf("Press Start to exit.\n");
    
    while (aptMainLoop()) {
        hidScanInput();
        if (hidKeysDown() & KEY_START) break;
        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    
    gfxExit();
    return 0;
}
