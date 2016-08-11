/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2016 CERN
 * @author Tomasz Wlostowski <tomasz.wlostowski@cern.ch>
 * @author Maciej Suminski <maciej.suminski@cern.ch>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef __sim_plot_frame__
#define __sim_plot_frame__

/**
@file
Subclass of SIM_PLOT_FRAME_BASE, which is generated by wxFormBuilder.
*/

#include "sim_plot_frame_base.h"
#include "kiway_player.h"
#include <netlist_exporters/netlist_exporter_pspice.h>
#include <wx/event.h>

class SPICE_SIMULATOR;
class NETLIST_EXPORTER_PSPICE;
class SIM_PLOT_PANEL;
class SIM_THREAD;

/** Implementing SIM_PLOT_FRAME_BASE */
class SIM_PLOT_FRAME : public SIM_PLOT_FRAME_BASE
{
    public:
        /** Constructor */
        SIM_PLOT_FRAME( KIWAY* aKiway, wxWindow* aParent );
        ~SIM_PLOT_FRAME();

        void SetSchFrame( SCH_EDIT_FRAME* aSchFrame )
        {
            m_schematicFrame = aSchFrame;
        }

        void StartSimulation();
        void PauseSimulation();
        void ResumeSimulation();
        void StopSimulation();

        void NewPlot();

        void TogglePythonConsole();

    private:
        virtual void onClose( wxCloseEvent& aEvent );
        virtual void onNewPlot( wxCommandEvent& aEvent ) { NewPlot(); }
        virtual void onSimReport( wxThreadEvent& aEvent );
        virtual void onSimFinished( wxThreadEvent& aEvent );

        SIM_PLOT_PANEL* m_currentPlot;
        SCH_EDIT_FRAME* m_schematicFrame;
        NETLIST_EXPORTER_PSPICE* m_exporter;
        SPICE_SIMULATOR* m_simulator;
        wxWindow* m_pyConsole;
        SIM_THREAD* m_simThread;
        wxCriticalSection m_simThreadCS;

        friend class SIM_THREAD;
};

wxDEFINE_EVENT( wxEVT_SIM_REPORT, wxThreadEvent );
wxDEFINE_EVENT( wxEVT_SIM_FINISHED, wxThreadEvent );

#endif // __sim_plot_frame__
