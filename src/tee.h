#ifndef TEE
#define TEE

class Tee
{
public:
    Tee(int argc, char** argv);
    void Write();
public:
    Tee(const Tee&) = delete;
    Tee(Tee&&) = delete;

    Tee& operator=(const Tee&) = delete;
    Tee& operator=(Tee&&) = delete;
private:
    int GetFlags();
private:
    class Error
    {
    public:
        void operator()(const char* errorDescription);
    };
private:
    char m_Buffer[1024]{};
    char m_Filepath[256]{};
    char m_Flags[8]{};
    int m_CountFlags{};
    Error m_Err;
};

#endif // TEE