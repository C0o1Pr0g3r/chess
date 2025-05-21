#ifndef DRAWING_FUNCTIONS_H_INCLUDED
#define DRAWING_FUNCTIONS_H_INCLUDED

void DrawApp(void);
void DrawMainMenuScreen(void);
void DrawChessGameScreen(void);
inline void DrawStaticChessGameObjects(void);
inline void DrawWhoseMoveInscription(void);
inline void DrawChessboard(void);
inline void DrawPawnTransformation(void);
inline void DrawGameOverWindow(void);
inline void DrawGameOnPauseWindow(void);
inline void DrawOptionsWindow(void);
inline void DrawGameSaveWindow(void);
void DrawFigures(void);
void DrawSmallFigures(void);

#endif // DRAWING_FUNCTIONS_H_INCLUDED
