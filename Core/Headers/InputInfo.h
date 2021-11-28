struct InputInfo
{
public:
    int buy_acres;
    int sold_acres;
    int ate_bushels;
    int sown_acres;

    void Add(int place, int value)
    {
        switch (place)
        {
            case 0:
                buy_acres = value;
                break;
            case 1:
                sold_acres = value;
                break;
            case 2:
                ate_bushels = value;
                break;
            case 3:
                sown_acres = value;
                break;
        }
    }
};