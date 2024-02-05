/**
 * \file Token definitions
 * \author João Vitor Espig (JotaEspig)
 * \date 04 February, 2024
 * \version 04 February, 2024
 **/
#pragma once

namespace logic
{

/**
 * \brief Token
 * \author João Vitor Espig (JotaEspig)
 * \date 04 February, 2024
 * \version 04 February, 2024
 **/
struct Token
{
    /**
     * \brief Token Type
     * \author João Vitor Espig (JotaEspig)
     * \date 04 February, 2024
     * \version 04 February, 2024
     *
     * It can be UNKNOWN, OPERATOR, NUMBER or VARIABLE
     **/
    enum class Type
    {
        UNKNOWN
    };
};

} // namespace logic
