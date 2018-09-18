#include <iostream>
#include <functional>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <chrono>

#include <switch.h>
#include "collage.hpp"
#include "gzip/compress.hpp"
#include "gzip/decompress.hpp"

#include "patch_bin.h"

std::string patch;
std::string orig;
std::string patched;

std::string file_to_string(const std::string &fileName){
  std::ifstream ifs(fileName.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

  std::ifstream::pos_type fileSize = ifs.tellg();
  ifs.seekg(0, std::ios::beg);

  std::vector<char> bytes(fileSize);
  ifs.read(bytes.data(), fileSize);

  return std::string(bytes.data(), fileSize);
}

void write_patch_to_file() {
  std::ofstream out("sdmc:/patch.bin");
  auto target = file_to_string("sdmc:/target_dialog.txt");

  auto diff = collage::diff(orig, target);

  out << gzip::compress(diff.data(), diff.size());

  out.close();
}

void turn_screen_green() {
  u32 width, height;
  u32* framebuf;

  framebuf = (u32*) gfxGetFramebuffer((u32*)&width, (u32*)&height);

  u32 framebuf_size = height * width - 1;

  const u32 green = 0x00ff00ffU;

  std::fill_n<u32*, u32, u32>(framebuf, framebuf_size, green);
}

int main(int argc, char **argv) {
  bool exit = false;

  appletInitialize();
  gfxInitDefault();
  consoleInit(NULL);

  Result rc = romfsInit();

  if (R_FAILED(rc)) {
    std::cout << "romfsInit: " << rc << std::endl;
  } else {
    std::cout << "romfs Init Successful!" << std::endl;
    orig = file_to_string("romfs:/Content/Dialog/English.txt");

    //write_patch_to_file();

    patch = gzip::decompress(reinterpret_cast<const char*>(patch_bin), patch_bin_size);

    patched = collage::patch(orig, patch);

    // std::cout << patched.substr(patched.length() - 300) << std::endl;

    std::ofstream out("sdmc:/atmosphere/titles/01002B30028F6000/romfs/Content/Dialog/English.txt");
    out << patched;
    out.close();

    int renameStatus = rename("/atmosphere/titles/01002B30028F6000/exefs.nsp", "/atmosphere/titles/01002B30028F6000/exefs.nsp.bak");

    if (renameStatus != 0) {
    
    } else {
      exit = true;
    }
  }

  auto time = std::chrono::system_clock::now();

  // Main loop
  while(appletMainLoop()) {
    //Scan all the inputs. This should be done once for each frame
    hidScanInput();

    //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
    u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

    if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

    if (exit) turn_screen_green();

    if (exit) {
      int duration = (std::chrono::system_clock::now() - time).count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;

      if (duration > 1) {
        break;
      }
    }

    gfxFlushBuffers();
    gfxSwapBuffers();
  }

  romfsExit();
  gfxExit();
  appletSelfExit();
  return 0;
}

