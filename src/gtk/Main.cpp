// VisualBoyAdvance - Nintendo Gameboy/GameboyAdvance (TM) emulator.
// Copyright (C) 1999-2003 Forgotten
// Copyright (C) 2004 Forgotten and the VBA development team

// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2, or(at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

#include "Window.h"
#include "Intl.h"

int main(int argc, char * argv[])
{
	bool bShowVersion = false;
	Glib::OptionGroup::vecustrings listRemaining;

#ifdef ENABLE_NLS
	setlocale(LC_ALL, "");
	bindtextdomain(GETTEXT_PACKAGE, LOCALEDIR);
	textdomain(GETTEXT_PACKAGE);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
#endif // ENABLE_NLS

	// Tell GSettings it can use the schemas from the build dir if they
	// have not been installed yet
	Glib::setenv("GSETTINGS_SCHEMA_DIR", "gsettings/");

	Glib::set_application_name(_("VBA-M"));

	Gtk::Main oKit(argc, argv);

	Glib::OptionContext oContext;
	Glib::OptionGroup oGroup("main_group", _("Main VBA-M options"));

	Glib::OptionEntry oVersion;
	oVersion.set_long_name("version");
	oVersion.set_short_name('v');
	oVersion.set_description(_("Output version information."));
	oGroup.add_entry(oVersion, bShowVersion);

	Glib::OptionEntry oFileName;
	oFileName.set_long_name(G_OPTION_REMAINING);
	oFileName.set_description(G_OPTION_REMAINING);
	oGroup.add_entry(oFileName, listRemaining);

	oContext.set_main_group(oGroup);

	try
	{
		oContext.parse(argc, argv);
	}
	catch (const Glib::Error& e)
	{
		Gtk::MessageDialog oDialog(e.what(),
		                           false,
		                           Gtk::MESSAGE_ERROR,
		                           Gtk::BUTTONS_OK);
		oDialog.run();
		return 1;
	}

	if (bShowVersion)
	{
		g_print(_("VisualBoyAdvance version %s [GTK+]\n"), VERSION);
		exit(0);
	}

	Gtk::Window::set_default_icon_name("vbam");

	Glib::RefPtr<Gtk::Builder> poBuilder;
	try
	{
		poBuilder = Gtk::Builder::create_from_resource("/org/vba/ttb/ui/vbam.ui");
	}
	catch (const Gio::ResourceError & e)
	{
		Gtk::MessageDialog oDialog(e.what(),
		                           false,
		                           Gtk::MESSAGE_ERROR,
		                           Gtk::BUTTONS_OK);
		oDialog.run();
		return 1;
	}

	VBA::Window * poWindow = 0;
	poBuilder->get_widget_derived("MainWindow", poWindow);

	if (listRemaining.size() == 1)
	{
		// Display the window before loading the file
		poWindow->show();
		while (Gtk::Main::events_pending())
		{
			Gtk::Main::iteration();
		}

		poWindow->bLoadROM(listRemaining[0]);
	}

	Gtk::Main::run(*poWindow);
	delete poWindow;

	return 0;
}
