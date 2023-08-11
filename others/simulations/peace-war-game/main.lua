STRATEGIES_AMOUNT = 3
PIECEMAKER = 1
GENGHIS_KHAN = 2
TIT_FOR_TAT = 3

PEACE = 1
WAR = 2


local function get_choice_by_type(nation1, nation2)
    local choice = 0

    if nation1.type == PIECEMAKER then
        choice = PEACE
    elseif nation1.type == GENGHIS_KHAN then
        choice = WAR
    elseif nation1.type == TIT_FOR_TAT then
        local prev_opponent_choice = nation1.prev_iterations[nation2.id]
        choice = PEACE
        if prev_opponent_choice == WAR then
            choice = WAR
        end
    end

    return choice
end


local function interation(payoff, nation1, nation2)
    local choice1 = get_choice_by_type(nation1, nation2)
    local choice2 = get_choice_by_type(nation2, nation1)

    nation1.prev_iterations[nation2.id] = choice2
    nation2.prev_iterations[nation1.id] = choice1

    return payoff[choice1][choice2]
end


local function populate(population, weights, max)
    max = max or 100
    if weights == nil then
        weights = {}
        for _ = 1, STRATEGIES_AMOUNT do
            table.insert(weights, 1)
        end
    end

    local list = {}
    for i, value in ipairs(weights) do
        for _ = 1, value do
            table.insert(list, i)
            print(i)
        end
    end

    for i = 1, max do
        local idx = math.random(#list)
        local type = list[idx]
        population[i] = {
            id = i,
            type = type,
            prev_iterations = {},
            wealth = 0
        }
    end
end


local function simulate(payoff, population, rounds)
    local length = #population
    local idxs = {}
    for i = 1, length do
        table.insert(idxs, i)
    end

    for _ = 1, rounds do
        -- copy idxs
        local tmp_idxs = {}
        for i, x in pairs(idxs) do
            tmp_idxs[i] = x
        end

        local tmp_length = length
        while #tmp_idxs > 0 do
            local rand1 = math.random(tmp_length)
            local idx1 = tmp_idxs[rand1]
            tmp_length = tmp_length - 1
            table.remove(tmp_idxs, rand1)

            local rand2 = math.random(tmp_length)
            local idx2 = tmp_idxs[rand2]
            tmp_length = tmp_length - 1
            table.remove(tmp_idxs, rand2)

            local nation1 = population[idx1]
            local nation2 = population[idx2]

            local result = interation(payoff, nation1, nation2)
            population[idx1].wealth = population[idx1].wealth + result[1]
            population[idx2].wealth = population[idx2].wealth + result[2]
        end
    end
end


local function main()
    math.randomseed(os.time())
    local population = {}

    local payoff_matrix = {
        {{2, 2}, {0, 3}},
        {{3, 0}, {0, 0}}
    }

    print("Hello World")

    populate(population, {1, 1, 1}, 100)
    local a, b, c = 0, 0, 0
    for _, value in pairs(population) do
        if value.type == 1 then
            a = a + 1
        elseif value.type == 2 then
            b = b + 1
        elseif value.type == 3 then
            c = c + 1
        end
    end

    print("types")
    print("1", "2", "3", "total")
    print(a, b, c, a+b+c)
    simulate(payoff_matrix, population, 100000)

    table.sort(population, function (a, b)
        return a.wealth > b.wealth
    end)

    print("\nresults:")
    for i, x in pairs(population) do
        print(i, x.type, x.wealth)
    end
end


main()
