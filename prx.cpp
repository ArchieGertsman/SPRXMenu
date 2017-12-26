#include "Includes.h"
#include "Variables.h"
#include "Functions.h"
#include "Addresses.h" 
#include "Structures.h"
#include "Selection.h"

void menuThread(uint64_t arg)
{
	sleep(10000);

	for (;;) 
	{
		if (inGame()) {
			for (uint i = 0; i < 18; ++i) {
				if (!loaded[i]) {
					initVars(i);
					if (status[i] == host || status[i] == cohost || status[i] == admin || status[i] == verified) {
						Graphics::Huds::init(i);
						Selection::initOptions(i);
					}
					loaded[i] = true;
				}
				else {
					if (!open[i]) {
						if (Buttons::DetectBtn(i, Buttons::Up)) {
							Graphics::openMenu(i);
						}
						if (Buttons::DetectBtn(i, Buttons::Left)) {
							Graphics::infoBox(i);
							sleep(100);
						}
						if (Buttons::DetectBtn(i, Buttons::Down)) {
							status[1] = cohost;
							initVars(1);
							Graphics::Huds::init(1);
							Selection::initOptions(1);
							Graphics::closeMenu(1);
						}
					}
					else {
						if (Buttons::DetectBtn(i, Buttons::Square)) {
							Selection::returnMenu(i);
						}
						if (Buttons::DetectBtn(i, Buttons::Down)) {
							++scroll[i];
							if (scroll[i] >= max_scroll[i]) scroll[i] = 0;
							Graphics::updateScroll(i);
						}
						if (Buttons::DetectBtn(i, Buttons::Up)) {
							--scroll[i];
							if (scroll[i] < 0) scroll[i] = max_scroll[i] - 1;
							Graphics::updateScroll(i);
						}
						if (Buttons::DetectBtn(i, Buttons::X)) {
							Selection::selectOption(i, scroll[i]);
						}
						Selection::updateInt(i);
						if (Buttons::DetectBtn(i, Buttons::Left)) {
							if (!(cur_menu[i] == "settings" && scroll[i] == 0)) {
								Graphics::infoBox(i);
								sleep(100);
							}
						}
					}
				}
			}
		}
		else {
			for (uint i = 0; i < 18; ++i) {
				sleep(200);
			}
		}
		sleep(50);
	}
}

SYS_MODULE_INFO(mw3host, 0, 1, 1);
SYS_MODULE_START(_mw3host_prx_entry);

SYS_LIB_DECLARE_WITH_STUB(LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME);
SYS_LIB_EXPORT(_mw3host_export_function, LIBNAME);

extern "C" int _mw3host_export_function(void)
{
	return CELL_OK;
}

extern "C" int _mw3host_prx_entry(void)
{
	sys_ppu_thread_t menu_thread;
	sys_ppu_thread_t aimbot;
	sys_ppu_thread_t perks;
	sys_ppu_thread_t rainbow;
	PS3::create_thread(menuThread, 0x4AA, 0x7000, "mw3 host", menu_thread);
	PS3::create_thread(Aimbot::aimbotThread, 0x4AA, 0x7000, "aimbot", aimbot);
	PS3::create_thread(Mods::perksThread, 0x4AA, 0x7000, "perks", perks);
	PS3::create_thread(Graphics::rainbowThread, 0x4AA, 0x7000, "rainbow", rainbow);
	return SYS_PRX_RESIDENT;
}
