#include <cstdio>

#include <iostream>

int main()
{


    char color_map[256];

    color_map['R'] = 0;
    color_map['G'] = 1;
    color_map['B'] = 2;
    color_map['Y'] = 3;
    color_map['O'] = 4;
    color_map['V'] = 5;

    int tests;

    std::cin >> tests;

    while(tests--)
    {
        char try1[10];
        int t1a, t1b;
        std::cin >> try1 >> t1a >> t1b;

        for(int i = 0 ; i < 4 ; ++i)
            try1[i] = color_map[try1[i]];

        char try2[10];
        int t2a, t2b;
        std::cin >> try2 >> t2a >> t2b;

        for(int i = 0 ; i < 4 ; ++i)
            try2[i] = color_map[try2[i]];

        bool found = false;

        for(int c1 = 0 ; c1 < 6 && !found ; ++c1)
            for(int c2 = 0 ; c2 < 6 && !found ; ++c2)
                for(int c3 = 0 ; c3 < 6 && !found ; ++c3)
                    for(int c4 = 0 ; c4 < 6 && !found ; ++c4)
                    {
                        if(c1 == c2 || c1 == c3 || c1 == c4 ||
                                c2 == c3 || c2 == c4 || c3 == c4 )
                            continue;

                        int guess[] = { c1, c2, c3, c4 };

                        int ga = 0, gb = 0;

                        for(int i = 0 ; i < 4 ; ++i)
                            if(try1[i] == guess[i])
                            {
                                ga++;
                                guess[i] = -1;
                            }

                        for(int i = 0 ; i < 4 ; ++i)
                            for(int j = 0 ; j < 4 ; ++j)
                            {
                                if(try1[i] == guess[j] && try1[j] != guess[j])
                                {
                                    gb++;
                                    guess[j] = -1;
                                }
                            }

                        if(t1a != ga || t1b != gb)
                            continue;

                        guess[0] = c1;
                        guess[1] = c2;
                        guess[2] = c3;
                        guess[3] = c4;
                        ga = gb = 0;

                        for(int i = 0 ; i < 4 ; ++i)
                            if(try2[i] == guess[i])
                            {
                                ga++;
                                guess[i] = -1;
                            }

                        for(int i = 0 ; i < 4 ; ++i)
                            for(int j = 0 ; j < 4 ; ++j)
                            {
                                if(try2[i] == guess[j] && try2[j] != guess[j])
                                {
                                    gb++;
                                    guess[j] = -1;
                                }
                            }

                        if(t2a != ga || t2b != gb)
                            continue;

                        found = true;
                    }
        if(found)
            std::cout << "Possible";
        else
            std::cout << "Cheat";
        std::cout << "\n";
    }

    return 0;
}
