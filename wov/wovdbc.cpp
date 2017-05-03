#include "dbc/DBC.h"
#include "mpq/MPQ.h"
#include "wovdbc.h"

// AnimationData.dbc
DBCFile& AnimationDataDBC::getDbc()
{
    static DBCFile dbc("AnimationData.dbc");
    return dbc;
}

const AnimationDataDBC::entry* AnimationDataDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString AnimationDataDBC::entry::name() const
{
    return getDbc().getString(nameOffset);
}

// CameraShakes.dbc
DBCFile& CameraShakesDBC::getDbc()
{
    static DBCFile dbc("CameraShakes.dbc");
    return dbc;
}

const CameraShakesDBC::entry* CameraShakesDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// CreatureDisplayInfo.dbc
DBCFile& CreatureDisplayInfoDBC::getDbc()
{
    static DBCFile dbc("CreatureDisplayInfo.dbc");
    return dbc;
}

const CreatureDisplayInfoDBC::entry* CreatureDisplayInfoDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString CreatureDisplayInfoDBC::entry::skin1() const
{
    return getDbc().getString(skin1Offset);
}

const QString CreatureDisplayInfoDBC::entry::skin2() const
{
    return getDbc().getString(skin2Offset);
}

const QString CreatureDisplayInfoDBC::entry::skin3() const
{
    return getDbc().getString(skin3Offset);
}

// CreatureModelData.dbc
DBCFile& CreatureModelDataDBC::getDbc()
{
    static DBCFile dbc("CreatureModelData.dbc");
    return dbc;
}

const CreatureModelDataDBC::entry* CreatureModelDataDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString CreatureModelDataDBC::entry::model() const
{
    return getDbc().getString(modelOffset);
}

// SpellEffectCameraShakes.dbc
DBCFile& SpellEffectCameraShakesDBC::getDbc()
{
    static DBCFile dbc("SpellEffectCameraShakes.dbc");
    return dbc;
}

const SpellEffectCameraShakesDBC::entry* SpellEffectCameraShakesDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellVisual.dbc
DBCFile& SpellVisualDBC::getDbc()
{
    static DBCFile dbc("SpellVisual.dbc");
    return dbc;
}

const SpellVisualDBC::entry* SpellVisualDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellVisualKit.dbc
DBCFile& SpellVisualKitDBC::getDbc()
{
    static DBCFile dbc("SpellVisualKit.dbc");
    return dbc;
}

const SpellVisualKitDBC::entry* SpellVisualKitDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

// SpellVisualEffectName.dbc
DBCFile& SpellVisualEffectNameDBC::getDbc()
{
    static DBCFile dbc("SpellVisualEffectName.dbc");
    return dbc;
}

const SpellVisualEffectNameDBC::entry* SpellVisualEffectNameDBC::getRecord(quint32 id, bool realId)
{
    return (realId ? getDbc().getEntry<entry>(id) : getDbc().getRecord<entry>(id));
}

const QString SpellVisualEffectNameDBC::entry::name() const
{
    return getDbc().getString(nameOffset);
}

const QString SpellVisualEffectNameDBC::entry::model() const
{
    return getDbc().getString(modelOffset);
}
