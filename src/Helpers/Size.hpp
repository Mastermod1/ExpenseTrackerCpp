namespace tracker::helpers
{
struct Size
{
    Size(int y, int x) : y{y}, x{x} {}


    int centeredXBy(const Size& s)
    {
	return (x - s.x)/2;
    }

    int centeredYBy(const Size& s)
    {
	return (y - s.y)/2;
    }

    int y = 0;
    int x = 0;
};
}  // namespace tracker::heleprs
