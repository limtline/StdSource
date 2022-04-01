class Sprite
{
public:
	IDirect3DTexture9* Texture;
	D3DXIMAGE_INFO imagesinfo;
	D3DCOLOR color;
public:
	Sprite(void);
	Sprite(Sprite&);
	~Sprite(void);
 
	Sprite& operator=(const Sprite&);

	bool Create(const char* filename, bool bUseTransparency, D3DCOLOR TransparencyColor);

	void Draw( float dx , float dy , float sx , float sy , float sw , float sh, float centerX = 0, float centerY = 0 ); // #92

	void Draw(float x, float y); // #01

	void Render( float x , float y , float radian, float sx, float sy);

	void RenderDraw( float x , float y , float sx , float sy , float sw , float sh, float radian, float sl, float st) ;

	void SetColor( int r , int g , int b , int a );
};

extern Sprite g_Load;