#ifndef _H_VISION
#define _H_VISION
struct vi_offset {
    int x,y,z;
};

typedef struct vi_offset VisionOffset;

class Vision {
    public:
        Vision();
        VisionOffset* get_object_offset();
    private:
        char mBuffer[15];
        VisionOffset mOffset;
};
#endif