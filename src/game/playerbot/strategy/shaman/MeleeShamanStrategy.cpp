#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "MeleeShamanStrategy.h"

using namespace ai;

class MeleeShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    MeleeShamanStrategyActionNodeFactory()
    {
        creators["stormstrike"] = &stormstrike;
        creators["lava lash"] = &lava_lash;
        creators["magma totem"] = &magma_totem;
    }
private:
    static ActionNode* stormstrike(PlayerbotAI* ai)
    {
        return new ActionNode ("stormstrike",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lava lash"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* lava_lash(PlayerbotAI* ai)
    {
        return new ActionNode ("lava lash",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* magma_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("magma totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("fire nova"), NULL));
    }
};

MeleeShamanStrategy::MeleeShamanStrategy(PlayerbotAI* ai) : GenericShamanStrategy(ai)
{
    actionNodeFactories.Add(new MeleeShamanStrategyActionNodeFactory());
}

NextAction** MeleeShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), new NextAction("stormstrike", 10.0f), new NextAction("lava lash", 10.0f), NULL);
}

void MeleeShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("windfury weapon", 22.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"lightning shield",
		NextAction::array(0, new NextAction("lightning shield", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "magma totem",
        NextAction::array(0, new NextAction("magma totem", 26.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "searing totem",
        NextAction::array(0, new NextAction("searing totem", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("fire nova", 25.0f), NULL)));
}