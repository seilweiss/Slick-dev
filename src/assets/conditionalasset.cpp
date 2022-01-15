#include "assets/conditionalasset.h"

#include "core/scene.h"

namespace Slick {

    namespace Assets {

        namespace {

            const QStringList varNames[(int)HipHop::Game::Count] =
            {
                {
                    "Chances",
                    "Scooby Snacks",
                    "Sound mode",
                    "Master Volume",
                    "Music Volume",
                    "SFX Volume",
                    "Bubble gum",
                    "Soap bar",
                    "Sticky boots",
                    "Plungers",
                    "Slippers",
                    "Lamp shade",
                    "Black knight",
                    "Flower pos",
                    "Diving helmet",
                    "Spring",
                    "Lightning bolt",
                    "Football helmet",
                    "Umbrella",
                    "Shovel",
                    "Memory Card Available",
                    "Vibration is on",
                    "Letter of scene",
                    "Room",
                    "IsSneaking",
                    "Map Item Recieved",
                    "R001 Unlocked",
                    "S001 Unlocked",
                    "F Piece Collected",
                    "L Piece Collected",
                    "W Piece Collected",
                    "E Piece Collected",
                    "C Piece Collected",
                    "G Piece Collected",
                    "P Piece Collected",
                    "B Piece Collected",
                    "S Piece Collected",
                    "I Piece Collected",
                    "R Piece Collected",
                    "O Piece Collected",
                    "H Piece Collected",
                    "F001 Unlocked",
                    "E001 Unlocked",
                    "Monster Token 1",
                    "Monster Token 2",
                    "Monster Token 3",
                    "Monster Token 4",
                    "Monster Token 5",
                    "Monster Token 6",
                    "Monster Token 7",
                    "Monster Token 8",
                    "Monster Token 9",
                    "Monster Token 10",
                    "Monster Token 11",
                    "Monster Token 12",
                    "Monster Token 13",
                    "Monster Token 14",
                    "Monster Token 15",
                    "Monster Token 16",
                    "Monster Token 17",
                    "Monster Token 18",
                    "Monster Token 19",
                    "Monster Token 20",
                    "Monster Token 21",
                    "Warp Point B4",
                    "Warp Point C4",
                    "Warp Point E4",
                    "Warp Point E6",
                    "Warp Point E9",
                    "Warp Point F3",
                    "Warp Point F7",
                    "Warp Point F10",
                    "Warp Point G1",
                    "Warp Point G5",
                    "Warp Point G8",
                    "Warp Point H1",
                    "Warp Point I3",
                    "Warp Point I6",
                    "Warp Point L14",
                    "Warp Point L15",
                    "Warp Point L18",
                    "Warp Point O4",
                    "Warp Point O6",
                    "Warp Point P3",
                    "Warp Point P5",
                    "Warp Point R3",
                    "Warp Point S3",
                    "Warp Point W22",
                    "Warp Point W26",
                    "Lightning bolt stun",
                    "Defeated Mastermind",
                    "Warp Point H3",
                    "AllSnacksBonus open",
                    "Cinematic 1 Unlocked",
                    "Cinematic 2 Unlocked",
                    "Cinematic 3 Unlocked",
                    "Cinematic 4 Unlocked",
                    "Cinematic 5 Unlocked",
                    "Cinematic 6 Unlocked",
                    "Cinematic 7 Unlocked",
                    "Cinematic 8 Unlocked",
                    "Cinematic 9 Unlocked",
                    "Cinematic 10 Unlocked",
                    "Cinematic 11 Unlocked",
                    "Cinematic 12 Unlocked",
                    "Cinematic 13 Unlocked",
                    "Cinematic 14 Unlocked"
                },
                {
                    "Sound mode",
                    "Music Volume",
                    "SFX Volume",
                    "Memory Card Available",
                    "Vibration is on",
                    "Letter of scene",
                    "Room",
                    "Current Level Collectable",
                    "Pat's Socks",
                    "Total Pat's Socks",
                    "Shiny Objects",
                    "Golden Spatulas",
                    "Current Date",
                    "Current Hour",
                    "Current Minute",
                    "Counter Value",
                    "Is Enabled (0=No, 1=Yes)",
                    "Is Visible (0=No, 1=Yes)"
                },
                {
                    "Sound mode",
                    "Music Volume",
                    "SFX Volume",
                    "Memory Card Available",
                    "Vibration is on",
                    "Subtitles are enabled",
                    "Letter of scene",
                    "Room",
                    "Current Date",
                    "Current Hour",
                    "Current Minute",
                    "Counter Value",
                    "Is Enabled (0=No, 1=Yes)",
                    "Is Visible (0=No, 1=Yes)",
                    "Timer Seconds Left",
                    "Timer Milliseconds Left",
                    "Is MNUS?",
                    "Demo Type",
                    "Goofy Goober Tokens",
                    "Manliness Points",
                    "Level Treasure Chests",
                    "Player Current Health",
                    "Is Reference NULL?",
                    "Always Portal"
                },
                {
                    "Sound mode",
                    "Music Volume",
                    "SFX Volume",
                    "Memory Card Available",
                    "Vibration is on",
                    "Subtitles are enabled",
                    "Letter of scene",
                    "Room",
                    "Current Date",
                    "Current Hour",
                    "Current Minute",
                    "Counter Value",
                    "Is Enabled (0=No, 1=Yes)",
                    "Is Visible (0=No, 1=Yes)",
                    "Timer Seconds Left",
                    "Timer Milliseconds Left",
                    "Is MNUS?",
                    "Demo Type",
                    "Is Reference NULL?",
                    "Hit Checkpoints",
                    "Total Checkpoints",
                    "Type of Pause Screen",
                    "User press Yes/Ok",
                    "User press no",
                    "User press back",
                    "Go Straight to Main Menu",
                    "Player Type",
                    "Is Signed In(0=No, 1=Yes)",
                    "Friend Request Received",
                    "Game Invite Received",
                    "Show English Videos"
                },
                {
                    "Sound mode",
                    "Music Volume",
                    "SFX Volume",
                    "Memory Card Available",
                    "Vibration is on Player1",
                    "Subtitles are enabled",
                    "Letter of scene",
                    "Room",
                    "Current Date",
                    "Current Hour",
                    "Current Minute",
                    "Counter Value",
                    "Is Enabled (0=No, 1=Yes)",
                    "Is Visible (0=No, 1=Yes)",
                    "Timer Seconds Left",
                    "Timer Milliseconds Left",
                    "Is MNUS?",
                    "Demo Type",
                    "Is Reference NULL?",
                    "Hit Checkpoints",
                    "Total Checkpoints",
                    "Type of Pause Screen",
                    "User press Yes/Ok",
                    "User press no",
                    "User press back",
                    "Go Straight to Main Menu",
                    "Player Type",
                    "Is Signed In(0=No, 1=Yes)",
                    "Friend Request Received",
                    "Game Invite Received",
                    "Show English Videos",
                    "Is Scene Unlocked?",
                    "Is Scene Completed?",
                    "Show Hints?",
                    "Upgrade MrI Health",
                    "Upgrade MrI Nuke",
                    "Upgrade MrI Melee",
                    "Upgrade MrI Throw",
                    "Upgrade MrI Slam",
                    "Upgrade Fro Health",
                    "Upgrade Fro Nuke",
                    "Upgrade Fro Melee",
                    "Upgrade Fro Freeze Ray",
                    "Upgrade Fro Ice Glide",
                    "Is One Player",
                    "Is Mr I AI Helper",
                    "Is Frozone AI Helper",
                    "Is Helper Loose Follow",
                    "Is Helper Close Follow",
                    "Is Helper Guard",
                    "Is PAL",
                    "Vibration is on Player2",
                    "Should Show Bonus Option",
                    "Is Language US",
                    "Is Language UK",
                    "Is Language DE",
                    "Is Language JP",
                    "Is Language KR",
                    "Is Language RU",
                    "Is Language ES",
                    "Is Language IT",
                    "Is Language FR"
                }
            };

            QList<uint32_t> varHashes[(int)HipHop::Game::Count] = {};
            bool varsInited = false;

            void initVars()
            {
                for (int i = 0; i < (int)HipHop::Game::Count; i++)
                {
                    const auto& names = varNames[i];

                    varHashes[i].reserve(names.size());

                    for (const auto& name : names)
                    {
                        varHashes[i].append(HipHop::Util::Hash(name.toStdString()));
                    }
                }

                varsInited = true;
            }

            class CondVariableProxy : public Inspector::Proxy<int>
            {
            public:
                CondVariableProxy(ConditionalAsset* asset) : m_cond(asset->serializer()), m_game(asset->scene()->game()) {}

                virtual int data() const override
                {
                    return varHashes[(int)m_game].indexOf(m_cond->value_asset);
                }

                virtual void setData(const int& data) const override
                {
                    if (data >= 0 && data < varHashes[(int)m_game].size())
                    {
                        m_cond->value_asset = varHashes[(int)m_game][data];
                    }
                }

            private:
                HipHop::CondAsset* m_cond;
                HipHop::Game m_game;
            };

        }

        ConditionalAsset::ConditionalAsset(HipHop::Asset asset, Core::SceneFile* sceneFile) :
            BaseAsset(asset, sceneFile),
            m_cond(asset)
        {
            if (!varsInited)
            {
                initVars();
            }

            setSerializer(&m_cond);
        }

        void ConditionalAsset::inspect(Inspector::Root* root)
        {
            BaseAsset::inspect(root);

            auto conditionalGroup = root->addGroup("conditional", tr("Conditional"));
            auto variableProp = conditionalGroup->addComboBox("variable", tr("Variable"), new CondVariableProxy(this), varNames[(int)scene()->game()]);
            auto operatorProp = conditionalGroup->addComboBox("operator", tr("Operator"), &m_cond.op, { "==", ">", "<", ">=", "<=", "!=" });
            auto valueProp = conditionalGroup->addNumberInput("value", tr("Value"), &m_cond.constNum);
            auto valueAssetProp = conditionalGroup->addAssetInput("valueAsset", tr("Value Asset"), &m_cond.value_asset, scene());

            connect(variableProp, &Inspector::Property::dataChanged, this, &ConditionalAsset::makeDirty);
            connect(operatorProp, &Inspector::Property::dataChanged, this, &ConditionalAsset::makeDirty);
            connect(valueProp, &Inspector::Property::dataChanged, this, &ConditionalAsset::makeDirty);
            connect(valueAssetProp, &Inspector::Property::dataChanged, this, &ConditionalAsset::makeDirty);

            inspectLinks(root);
        }

    }

}
