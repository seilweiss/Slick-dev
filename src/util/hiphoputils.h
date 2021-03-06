#pragma once

#include "hiphop.h"

#include <QString>

namespace Slick {

    namespace Util {

        inline QString assetTypeToString(HipHop::AssetType type)
        {
            uint32_t t = (uint32_t)type;
            HipHop::Util::Swap32(&t, sizeof(uint32_t));

            return QString::fromUtf8((char*)&t, sizeof(uint32_t));
        }

        inline QString layerTypeToString(HipHop::LayerType type)
        {
            switch (type)
            {
            case HipHop::LayerType::DEFAULT: return "DEFAULT";
            case HipHop::LayerType::TEXTURE: return "TEXTURE";
            case HipHop::LayerType::TEXTURE_STRM: return "TEXTURE_STRM";
            case HipHop::LayerType::BSP: return "BSP";
            case HipHop::LayerType::MODEL: return "MODEL";
            case HipHop::LayerType::ANIMATION: return "ANIMATION";
            case HipHop::LayerType::VRAM: return "VRAM";
            case HipHop::LayerType::SRAM: return "SRAM";
            case HipHop::LayerType::SNDTOC: return "SNDTOC";
            case HipHop::LayerType::CUTSCENE: return "CUTSCENE";
            case HipHop::LayerType::CUTSCENETOC: return "CUTSCENETOC";
            case HipHop::LayerType::JSPINFO: return "JSPINFO";
            default: return "<unknown>";
            }
        }

        inline QStringList eventNames(HipHop::Game game)
        {
            if (game < HipHop::Game::ScoobyNightOf100Frights || game > HipHop::Game::RiseOfTheUnderminer)
            {
                game = HipHop::Game::RiseOfTheUnderminer;
            }

            static QStringList names[(int)HipHop::Game::Count];
            static bool init[(int)HipHop::Game::Count] = { false };

            if (!init[(int)game])
            {
                int count;

                switch (game)
                {
                case HipHop::Game::ScoobyNightOf100Frights:
                    count = HipHop::Event::CountScooby;
                    break;
                case HipHop::Game::BattleForBikiniBottom:
                    count = HipHop::Event::CountBFBB;
                    break;
                case HipHop::Game::SpongeBobMovie:
                    count = HipHop::Event::CountTSSM;
                    break;
                case HipHop::Game::Incredibles:
                case HipHop::Game::RiseOfTheUnderminer:
                default:
                    count = HipHop::Event::CountIncredibles;
                    break;
                }

                for (int i = 0; i < count; i++)
                {
                    names[(int)game].append(QString::fromStdString(HipHop::EventToString(i, game)));
                }

                init[(int)game] = true;
            }

            return names[(int)game];
        }

    }

}
