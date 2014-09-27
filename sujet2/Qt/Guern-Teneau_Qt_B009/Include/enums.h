#ifndef ENUMS
#define ENUMS

enum toolsID {
	TOOLS_ID_FREEHAND, 
	TOOLS_ID_LINE, 
	TOOLS_ID_RECTANGLE,
	TOOLS_ID_CIRCLE, 
	TOOLS_ID_POLYGON, 
    TOOLS_ID_TEXT
};

enum menusID{
	FILE_MENU_ID_NEW,
	FILE_MENU_ID_OPEN, 
	FILE_MENU_ID_SAVE, 
	FILE_MENU_ID_SAVE_AS,
	TOOLS_MENU_ID_FREEHAND, 
	TOOLS_MENU_ID_LINE, 
	TOOLS_MENU_ID_CIRCLE, 
    TOOLS_MENU_ID_RECTANGLE,
	TOOLS_MENU_ID_POLYGON, 
	TOOLS_MENU_ID_TEXT, 
	STYLE_MENU_ID_PEN, 
	STYLE_MENU_ID_BRUSH, 
	STYLE_MENU_ID_FONT
};

//http://qt-project.org/doc/qt-4.8/painting-basicdrawing.html
enum stylePenID {
        STYLE_PEN_ID_SOLID,
        STYLE_PEN_ID_DASH,
        STYLE_PEN_ID_DOT,
        STYLE_PEN_ID_DASHDOT,
        STYLE_PEN_ID_DASHDOTNOT,
        STYLE_PEN_ID_NONE
};

enum capPenID {
        CAP_PEN_ID_FLAT,
        CAP_PEN_ID_SQUARE,
        CAP_PEN_ID_ROUND
};

enum joinPenID {
        JOIN_PEN_ID_MITER,
        JOIN_PEN_ID_BEVEL,
        JOIN_PEN_ID_ROUND
};

enum styleBrushID {
        STYLE_BRUSH_ID_LINEARGRADIENT,
        STYLE_BRUSH_ID_RADIALGRADIENT,
        STYLE_BRUSH_ID_CONICALGRADIENT,
        STYLE_BRUSH_ID_TEXTURE,
        STYLE_BRUSH_ID_SOLID,
        STYLE_BRUSH_ID_HORIZONTAL,
        STYLE_BRUSH_ID_VERTICAL,
        STYLE_BRUSH_ID_CROSS,
        STYLE_BRUSH_ID_BACKWARDDIAGONAL,
        STYLE_BRUSH_ID_FORWARDDIAGONAL,
        STYLE_BRUSH_ID_DIAGONALCROSS,
        STYLE_BRUSH_ID_DENSE1,
        STYLE_BRUSH_ID_DENSE2,
        STYLE_BRUSH_ID_DENSE3,
        STYLE_BRUSH_ID_DENSE4,
        STYLE_BRUSH_ID_DENSE5,
        STYLE_BRUSH_ID_DENSE6,
        STYLE_BRUSH_ID_DENSE7,
        STYLE_BRUSH_ID_NONE
};

#endif

