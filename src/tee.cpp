#include "tee.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

Tee::Tee(int argc, char** argv)
{
    if (argc >= 2)
    {
        int iter{1};
        for (; iter < argc; ++iter)
        {
            size_t szArg = strlen(argv[iter]);
            if (szArg == 2 && argv[iter][0] == '-')
            {
                m_Flags[m_CountFlags] = argv[iter][1];
                ++m_CountFlags;
            }
        }

        if ((argc - 1) != m_CountFlags)
        {
            strcpy(m_Filepath, argv[argc-1]);
        }
        else
        {
            m_Err("Need to set file path or file name after options");
        }
        
    }
    else
    {
        m_Err("Output file name required");
    }
}

void Tee::Write()
{
    int flags = GetFlags();

    int outfd = open(m_Filepath, flags, 0644);
    if (outfd != -1)
    {
        ssize_t nread = 0;
        while((nread = read(STDIN_FILENO, m_Buffer, 1024)) != 0) 
        {
            if (write(STDOUT_FILENO, m_Buffer, nread) != nread)
                m_Err("Failed to write to stdout");

            if (write(outfd, m_Buffer, nread) != nread)
                m_Err("Failed to write to file");
        };
    }
    else
    {
        m_Err("Failed to create output file");
    }
}

int Tee::GetFlags()
{
    int flags{};

    flags |= O_WRONLY;

    for (int iter{}; iter < m_CountFlags; ++iter)
    {
        switch (m_Flags[iter])
        {
            case 'a':   flags |= O_APPEND;
            // TODO: more options
        }
    }

    if (!(flags & O_APPEND))
        flags |= (O_CREAT | O_TRUNC);

    return flags;
}

void Tee::Error::operator()(const char* errorDescription) { fprintf(stderr, "%s\n", errorDescription); _exit(1); }