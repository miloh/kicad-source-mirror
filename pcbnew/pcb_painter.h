/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2013 CERN
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

#ifndef __CLASS_PCB_PAINTER_H
#define __CLASS_PCB_PAINTER_H

#include <layers_id_colors_and_visibility.h>

#include <painter.h>


class EDA_ITEM;
class COLORS_DESIGN_SETTINGS;
class DISPLAY_OPTIONS;

class BOARD_ITEM;
class BOARD;
class SEGVIA;
class TRACK;
class D_PAD;
class DRAWSEGMENT;
class MODULE;
class SEGZONE;
class ZONE_CONTAINER;
class TEXTE_PCB;
class TEXTE_MODULE;
class DIMENSION;
class PCB_TARGET;

namespace KiGfx
{
class GAL;
class STROKE_FONT;

/**
 * Class PCB_RENDER_SETTINGS
 * Stores PCB specific render settings.
 */
class PCB_RENDER_SETTINGS : public RENDER_SETTINGS
{
public:

    friend class PCB_PAINTER;

    enum ClearanceMode {
        CL_VIAS     = 0x1,
        CL_PADS     = 0x2,
        CL_TRACKS   = 0x4
    };

    PCB_RENDER_SETTINGS();

    /// @copydoc RENDER_SETTINGS::Update()
    void Update();

    /// @copydoc RENDER_SETTINGS::ImportLegacyColors()
    void ImportLegacyColors( COLORS_DESIGN_SETTINGS* aSettings );

    /**
     * Function LoadDisplayOptions
     * Loads settings related to display options (high-contrast mode, full or outline modes
     * for vias/pads/tracks and so on).
     * @param aOptions are settings that you want to use for displaying items.
     */
    void LoadDisplayOptions( const DISPLAY_OPTIONS& aOptions );

protected:

    /// Colors for all layers (including special, highlighted & darkened versions)
    COLOR4D m_layerColors    [LAYER_COUNT];
    COLOR4D m_layerColorsHi  [LAYER_COUNT];
    COLOR4D m_layerColorsSel [LAYER_COUNT];
    COLOR4D m_layerColorsDark[LAYER_COUNT];
    COLOR4D m_itemColors     [END_PCB_VISIBLE_LIST];
    COLOR4D m_itemColorsHi   [END_PCB_VISIBLE_LIST];
    COLOR4D m_itemColorsSel  [END_PCB_VISIBLE_LIST];
    COLOR4D m_itemColorsDark [END_PCB_VISIBLE_LIST];

    bool    m_sketchModeSelect[END_PCB_VISIBLE_LIST];
    bool    m_visibleLayers   [LAYER_COUNT];
    bool    m_visibleItems    [END_PCB_VISIBLE_LIST];
};


/**
 * Class PCB_PAINTER
 * Contains methods for drawing PCB-specific items.
 */
class PCB_PAINTER : public PAINTER
{
public:

    PCB_PAINTER( GAL* aGal );

    /// @copydoc PAINTER::Draw()
    virtual bool Draw( const EDA_ITEM*, int );

    /// @copydoc PAINTER::ApplySettings()
    virtual void ApplySettings( RENDER_SETTINGS* aSettings )
    {
        PAINTER::ApplySettings( aSettings );

        // Store PCB specific render settings
        m_pcbSettings = dynamic_cast<PCB_RENDER_SETTINGS*> ( aSettings );
    }

protected:

    PCB_RENDER_SETTINGS* m_pcbSettings;

    /// @copydoc PAINTER::getLayerColor()
    const COLOR4D& getLayerColor( int aLayer, int aNetCode ) const;

    /**
     * Function getItemColor
     * Returns color for a special layer (eg. vias/pads holes, texts on front/bottom layer, etc.)
     * @param aItemType Layer number of the item to be drawn.
     * @param aNetCode Net number of the item to be drawn.
     */
    const COLOR4D& getItemColor( int aItemType, int aNetCode ) const;

    // Drawing functions for various types of PCB-specific items
    void draw( const TRACK* );
    void draw( const SEGVIA*, int );
    void draw( const D_PAD*, int );
    void draw( const DRAWSEGMENT* );
    void draw( const TEXTE_PCB* );
    void draw( const TEXTE_MODULE*, int );
    void draw( const ZONE_CONTAINER* );
    void draw( const DIMENSION* );
    void draw( const PCB_TARGET* );
};
} // namespace KiGfx

#endif /* __CLASS_PAINTER_H */