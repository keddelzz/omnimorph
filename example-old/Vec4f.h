#include <cstring>
#include <QCore/QString>
#include <QCore/QObject.h>

struct Vec4f
{
    generic(Vec4f)

    float x = 0;
public:
    float y;
private:
    float z;
    struct Test {
        int x { -3 };
    };
protected:
    float w;
};

struct Vec2f
{
    int x;
    int y;
};