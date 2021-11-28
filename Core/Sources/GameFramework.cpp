#include "../Headers/GameFramework.h"

void GameFramework::StartGame()
{
    stats = {kStartPopulation, kStartWheat, kStartAcres};
    bool is_continue = false;
    if(saver.IsFileExist())
    {
        char input;
        std::cout << "Обнаружен файл сохранения. Загрузить? (y-да): ";
        std::cin >> input;
        if(input == 'y')
        {
            saver.TryLoad(roundInfo);
            stats = roundInfo.playerStats;
            is_continue = true;
        }
        else
        {
            is_continue = false;
        }
    }
    ShowStartInfo();
    GameLoop(is_continue);
}

void GameFramework::ShowStartInfo() const
{
    SeparateText();
    std::cout << "НАЧАЛЬНЫЕ РЕСУРСЫ\n"
              << "Популяция: " << stats.population
              << "\nАкров: " << stats.acres
              << "\nБушелей: " << stats.wheat << std::endl;
}

void GameFramework::GameOver()
{
    std::cout << "Вы проиграли! Умерло больше 45% населения от голода за раунд\n";
    Retry();
}

void GameFramework::GameLoop(bool isContinueGame)
{
    int current_round = 0;
    if(isContinueGame)
    {
        ShowRoundInfo(roundInfo);
        current_round = roundInfo.current_round;
    }

    bool exit = false;

    ValidateInfo validateInfo;
    InputInfo inputInfo{};

    int was_population;

    while (!exit && current_round < kMaxRounds)
    {
        //валидация значений
        validateInfo.cost_per_acr = GetRandomValue(kMinCostPerAcr, kMaxCostPerAcr);
        validateInfo.max_acres_can_buy = stats.wheat / validateInfo.cost_per_acr;
        validateInfo.max_acres_can_sold = stats.acres;
        validateInfo.max_wheat_can_eat = stats.wheat;
        validateInfo.max_acres_can_process = stats.population * kMaxProcessAcres;
        was_population = stats.population;

        //ввод и потеря/приобретение сопутствующих ресурсов
        SeparateText();
        inputInfo = core.ReadInput(validateInfo, stats);
        SeparateText();

        //вернули то, что отложили на еду
        stats.wheat += inputInfo.ate_bushels;

        //собрали пшена
        int wheat_per_acre = GetRandomValue(kMinWheatPerAcr, kMaxWheatPerAcr);
        int picked_wheat = inputInfo.sown_acres * wheat_per_acre;
        if (picked_wheat > validateInfo.max_acres_can_process)
            picked_wheat = validateInfo.max_acres_can_process;
        stats.wheat += picked_wheat;


        //крысы съели пшено
        int max_dead_wheat = static_cast<int>(0.07 * stats.wheat);
        int dead_wheat = GetRandomValue(0, max_dead_wheat);
        stats.wheat -= dead_wheat;


        //съели и умерли те, кому не хватило
        int people_per_food = floor(inputInfo.ate_bushels / 20.0);
        int dead_people = stats.population - people_per_food;
        if (dead_people > 0)
            stats.population -= dead_people;
        else
            dead_people = 0;

        //съели пшена люди
        stats.wheat -= people_per_food * 20;

        //новые люди
        int new_people_check = static_cast<int>
        (static_cast<double>
         (dead_people) / 2 + (5 - wheat_per_acre) * stats.wheat / 600 + 1);
        int new_people = new_people_check <= 0 ? 0 : new_people_check;
        stats.population += new_people;

        //чума и последствия
        int plague_chance = GetRandomValue(0, 100);
        bool was_plague = plague_chance <= 15;
        if (was_plague)
        {
            stats.population = floor(stats.population / 2.0);
        }

        //процент умерших за раунд
        double dead_percent = static_cast<double>(dead_people) / was_population;
        dead_percentage.push_back(dead_percent);
        if (dead_percent > 0.45)
        {
            GameOver();
            return;
        }

        current_round++;
        roundInfo =
                {
                        current_round, dead_people, new_people, was_plague,
                        picked_wheat, wheat_per_acre, dead_wheat, stats.acres, validateInfo.cost_per_acr, stats
                };

        ShowRoundInfo(roundInfo);
        if(current_round != 10)
        {
            exit = TryExitGame();
            saver.Save(roundInfo);
        }
    }
    if(current_round == kMaxRounds)
        WinGame();
}

void GameFramework::SeparateText() const
{
    std::cout << "----------------------------------------------------------------------\n";
}

int GameFramework::GetRandomValue(int minValue, int maxValue)
{
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution distrib(minValue, maxValue);
    return distrib(generator);
}

bool GameFramework::TryExitGame()
{
    char input;
    std::cout << "Повелитель, желаешь отдохнуть от своих дел? (y - выйти): ";
    std::cin >> input;
    return input == 'y';
}

void GameFramework::ShowRoundInfo(RoundInfo &roundInfo)
{
    std::cout << "Мой повелитель, соизволь поведать тебе о текущем состоянии дел в городе:\n";

    printf("\tВ году %d твоего высочайшего правления\n", roundInfo.current_round);

    if (roundInfo.dead_people > 0)
    {
        std::cout << "\t" << roundInfo.dead_people << " человек умерли с голоду";
        if (roundInfo.new_people > 0)
        {
            std::cout << ", и ";
        } else
        {
            std::cout << ";\n";
        }
    }

    if (roundInfo.new_people > 0)
    {
        if (roundInfo.dead_people <= 0)
        {
            std::cout << "\t";
        }
        std::cout << roundInfo.new_people << " человек прибыли в наш великий город;\n";
    }

    std::cout << "\t" << (roundInfo.was_plague ? "Чума уничтожила половину населения;"
                                               : "В этом году обошлось без чумы;") << "\n";
    printf("\tНаселение города сейчас составляет %d человек;\n"
           "\tМы собрали %d бушелей пшеницы, по %d бушеля с акра;\n"
           "\tКрысы истребили %d бушелей пшеницы, оставив %.1f бушеля в амбарах;\n"
           "\tГород сейчас занимает %d акров;\n"
           "\t1 акр земли сейчас стоит %d бушель.\n",
           roundInfo.playerStats.population, roundInfo.bushels_picked, roundInfo.bushels_per_acre, roundInfo.dead_bushels,
           roundInfo.playerStats.wheat, roundInfo.town_acres, roundInfo.cost_per_acre);
}

void GameFramework::WinGame()
{
    double sum = 0;
    for (double percent : dead_percentage)
    {
        sum += percent;
    }
    P = sum / dead_percentage.size();
    L = static_cast<double>(stats.population) / stats.acres;

    if (P > 0.33 && L < 7)
    {
        std::cout << "Из-за вашей некомпетентности в управлении, народ устроил бунт, и изгнал вас их города. Теперь "
                     "вы вынуждены влачить жалкое существование в изгнании\n";
    }
    else if(P > 0.1 && L < 9)
    {
        std::cout << "«Вы правили железной рукой, подобно Нерону и Ивану Грозному. Народ вздохнул с облегчением, и "
                     "никто больше не желает видеть вас правителем\n";
    }
    else if(P > 0.03 && L < 10)
    {
        std::cout << "«Вы справились вполне неплохо, у вас, конечно, есть недоброжелатели, но многие хотели бы "
                     "увидеть вас во главе города снова»\n";
    }
    else
    {
        std::cout << "Фантастика! Карл Великий, Дизраэли и Джефферсон вместе не справились бы лучше\n";
    }
    Retry();
}

void GameFramework::Retry()
{
    char input;
    std::cout << "Хотите начать новую игру? (y - да, n - нет): ";
    std::cin >> input;
    if (input == 'y')
    {
        dead_percentage.clear();
        StartGame();
    }
}