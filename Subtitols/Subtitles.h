#ifndef CSUBTITLES_H
#define CSUBTITLES_H

class CSubtitles
{
private:

	GLfloat red, green, blue, alpha;
	GLfloat posX, posY;
	char* subtitle;

public:

	CSubtitles();
	~CSubtitles();

	void		SetColor			( float r, float g, float b, float a );
	void		SetPosition			( float x, float y );
	void		SetText				( char* text );

	void		ParseSubtitles		( void );
	void		RenderSubtitles		( void );

};

#endif