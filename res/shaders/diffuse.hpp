class diffuse
{
public:
	diffuse(float bias);
	~diffuse(void);

	void operator()(sb::rs::Image &diffuse, sb::rs::Image &normal_map);
};