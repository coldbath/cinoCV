#include "fileProcess.h"

namespace cino
{
    int createDirectory(std::string directoryPath)
    {
        int dirPathLen = directoryPath.length();
        if (dirPathLen > 256)
        {
            return -1;
        }
        char tmpDirPath[256] = {0};
        for (uint32_t i = 0; i < dirPathLen; ++i)
        {
            tmpDirPath[i] = directoryPath[i];
            if (tmpDirPath[i] == '\\' || tmpDirPath[i] == '/')
            {
                if (access(tmpDirPath, 0) != 0)
                {
                    int32_t ret = mkdir(tmpDirPath, 0777);
                    if (ret != 0)
                    {
                        return -1;
                    }
                }
            }
        }
        return 0;
    }

    int copyFile(std::string srcPath, std::string dstPath)
    {
        std::ifstream in;
        std::ofstream out;

        in.open(srcPath, std::ios::binary);

        if (in.fail())
        {
            std::cout << "Fail to open the source file." << std::endl;
            in.close();
            out.close();
            return 0;
        }

        out.open(dstPath, std::ios::binary);

        if (out.fail())
        {
            std::cout << "Fail to create the dst file." << std::endl;
            out.close();
            in.close();
            return 0;
        }
        else
        {
            out << in.rdbuf();
            out.close();
            in.close();
            return 1;
        }
    }

} // namespace cino
