class diffuse
{
public:
	diffuse(float bias);
	~diffuse(void);

	void operator()(sb::rs::Texture &diffuse, sb::rs::Texture &normal_map);
};