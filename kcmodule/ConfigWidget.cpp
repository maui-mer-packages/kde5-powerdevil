#include "ConfigWidget.h"

#include "PowerDevilSettings.h"

#include <solid/control/powermanager.h>

ConfigWidget::ConfigWidget(QWidget *parent)
  : QWidget(parent)
{
    setupUi(this);

    fillUi();
}

void ConfigWidget::fillUi()
{
    
    PoweredIdleCombo->addItem("Do nothing", 0);
    PoweredIdleCombo->addItem("Shutdown", Shutdown);
    BatteryCriticalCombo->addItem("Do nothing", 0);
    BatteryCriticalCombo->addItem("Shutdown", Shutdown);
    BatteryIdleCombo->addItem("Do nothing", 0);
    BatteryIdleCombo->addItem("Shutdown", Shutdown);

    Solid::Control::PowerManager::SuspendMethods methods = Solid::Control::PowerManager::supportedSuspendMethods();

    if(methods | Solid::Control::PowerManager::ToDisk)
    {
        PoweredIdleCombo->addItem("Suspend to Disk", S2Disk);
        BatteryCriticalCombo->addItem("Suspend to Disk", S2Disk);
        BatteryIdleCombo->addItem("Suspend to Disk", S2Disk);
    }
    if(methods | Solid::Control::PowerManager::ToRam)
    {
        PoweredIdleCombo->addItem("Suspend to Ram", S2Ram);
        BatteryCriticalCombo->addItem("Suspend to Ram", S2Ram);
        BatteryIdleCombo->addItem("Suspend to Ram", S2Ram);
    }
    if(methods | Solid::Control::PowerManager::Standby)
    {
        PoweredIdleCombo->addItem("Standby", Standby);
        BatteryCriticalCombo->addItem("Standby", Standby);
        BatteryIdleCombo->addItem("Standby", Standby);
    }

    Solid::Control::PowerManager::CpuFreqPolicies policies = Solid::Control::PowerManager::supportedCpuFreqPolicies();

    if(policies | Solid::Control::PowerManager::Performance)
    {
        PoweredFreqCombo->addItem("Performance", (int) Solid::Control::PowerManager::Performance);
        BatteryFreqCombo->addItem("Performance", (int) Solid::Control::PowerManager::Performance);
    }
    if(policies | Solid::Control::PowerManager::OnDemand)
    {
        PoweredFreqCombo->addItem("Dynamic (aggressive)", (int) Solid::Control::PowerManager::OnDemand);
        BatteryFreqCombo->addItem("Dynamic (aggressive)", (int) Solid::Control::PowerManager::OnDemand);
    }
    if(policies | Solid::Control::PowerManager::Conservative)
    {
        PoweredFreqCombo->addItem("Dynamic (less agressive)", (int) Solid::Control::PowerManager::Conservative);
        BatteryFreqCombo->addItem("Dynamic (less agressive)", (int) Solid::Control::PowerManager::Conservative);
    }
    if(policies | Solid::Control::PowerManager::Powersave)
    {
        PoweredFreqCombo->addItem("Powersave", (int) Solid::Control::PowerManager::Powersave);
        BatteryFreqCombo->addItem("Powersave", (int) Solid::Control::PowerManager::Powersave);
    }

    // modified fields...

    connect(lockScreenOnResume, SIGNAL(stateChanged(int)), SLOT(emitChanged()));
    connect(dimDisplayOnIdle, SIGNAL(stateChanged(int)), SLOT(emitChanged()));

    connect(PoweredBrightnessSlider, SIGNAL(valueChanged(int)), SLOT(emitChanged()));
    connect(PoweredOffDisplayWhenIdle, SIGNAL(stateChanged(int)), SLOT(emitChanged()));
    connect(PoweredDisplayIdleTime, SIGNAL(valueChanged(int)), SLOT(emitChanged()));
    connect(PoweredIdleTime, SIGNAL(valueChanged(int)), SLOT(emitChanged()));
    connect(PoweredIdleCombo, SIGNAL(currentIndexChanged(int)), SLOT(emitChanged()));
    connect(PoweredFreqCombo, SIGNAL(currentIndexChanged(int)), SLOT(emitChanged()));

    connect(BatteryBrightnessSlider, SIGNAL(valueChanged(int)), SLOT(emitChanged()));
    connect(BatteryOffDisplayWhenIdle, SIGNAL(stateChanged(int)), SLOT(emitChanged()));
    connect(BatteryDisplayIdleTime, SIGNAL(valueChanged(int)), SLOT(emitChanged()));
    connect(BatteryIdleTime, SIGNAL(valueChanged(int)), SLOT(emitChanged()));
    connect(BatteryIdleCombo, SIGNAL(currentIndexChanged(int)), SLOT(emitChanged()));
    connect(BatteryCriticalCombo, SIGNAL(currentIndexChanged(int)), SLOT(emitChanged()));
    connect(BatteryFreqCombo, SIGNAL(currentIndexChanged(int)), SLOT(emitChanged()));
}

void ConfigWidget::load()
{
    lockScreenOnResume->setChecked(PowerDevilSettings::configLockScreen());
    dimDisplayOnIdle->setChecked(PowerDevilSettings::dimOnIdle());
    PoweredBrightnessSlider->setValue(PowerDevilSettings::aCBrightness());
    PoweredOffDisplayWhenIdle->setChecked(PowerDevilSettings::aCOffDisplayWhenIdle());
    PoweredDisplayIdleTime->setValue(PowerDevilSettings::aCDisplayIdle());
    PoweredIdleTime->setValue(PowerDevilSettings::aCIdle());
    PoweredIdleCombo->setCurrentIndex(PoweredIdleCombo->findData(PowerDevilSettings::aCIdleAction()));
    PoweredFreqCombo->setCurrentIndex(PoweredFreqCombo->findData(PowerDevilSettings::aCCpuPolicy()));
    BatteryBrightnessSlider->setValue(PowerDevilSettings::batBrightness());
    BatteryOffDisplayWhenIdle->setChecked(PowerDevilSettings::batOffDisplayWhenIdle());
    BatteryDisplayIdleTime->setValue(PowerDevilSettings::batDisplayIdle());
    BatteryIdleTime->setValue(PowerDevilSettings::batIdle());
    BatteryIdleCombo->setCurrentIndex(BatteryIdleCombo->findData(PowerDevilSettings::batIdleAction()));
    BatteryCriticalCombo->setCurrentIndex(BatteryCriticalCombo->findData(PowerDevilSettings::batLowAction()));
    BatteryFreqCombo->setCurrentIndex(BatteryFreqCombo->findData(PowerDevilSettings::batCpuPolicy()));

    switch(PowerDevilSettings::batLidAction())
    {
        case None:
            laptopClosedBatteryNone->setChecked(true);
            break;
        case S2Disk:
            laptopClosedBatteryHibernate->setChecked(true);
            break;
        case S2Ram:
            laptopClosedBatterySuspend->setChecked(true);
            break;
        case Shutdown:
            laptopClosedBatteryShutdown->setChecked(true);
            break;
        case Lock:
            laptopClosedBatteryBlank->setChecked(true);
            break;
        default:
            break;
    }
    switch(PowerDevilSettings::aCLidAction())
    {
        case None:
            laptopClosedACNone->setChecked(true);
            break;
        case S2Disk:
            laptopClosedACHibernate->setChecked(true);
            break;
        case S2Ram:
            laptopClosedACSuspend->setChecked(true);
            break;
        case Shutdown:
            laptopClosedACShutdown->setChecked(true);
            break;
        case Lock:
            laptopClosedACBlank->setChecked(true);
            break;
        default:
            break;
    }
}

void ConfigWidget::save()
{
    PowerDevilSettings::setConfigLockScreen(lockScreenOnResume->isChecked());
    PowerDevilSettings::setDimOnIdle(dimDisplayOnIdle->isChecked());

    PowerDevilSettings::setACBrightness(PoweredBrightnessSlider->value());
    PowerDevilSettings::setACOffDisplayWhenIdle(PoweredOffDisplayWhenIdle->isChecked());
    PowerDevilSettings::setACDisplayIdle(PoweredDisplayIdleTime->value());
    PowerDevilSettings::setACIdle(PoweredIdleTime->value());
    PowerDevilSettings::setACIdleAction(PoweredIdleCombo->currentIndex());
    PowerDevilSettings::setACCpuPolicy(PoweredFreqCombo->currentIndex());

    PowerDevilSettings::setBatBrightness(BatteryBrightnessSlider->value());
    PowerDevilSettings::setBatOffDisplayWhenIdle(BatteryOffDisplayWhenIdle->isChecked());
    PowerDevilSettings::setBatDisplayIdle(BatteryDisplayIdleTime->value());
    PowerDevilSettings::setBatIdle(BatteryIdleTime->value());
    PowerDevilSettings::setBatIdleAction(BatteryIdleCombo->currentIndex());
    PowerDevilSettings::setBatCpuPolicy(BatteryFreqCombo->currentIndex());
    PowerDevilSettings::setBatLowAction(BatteryCriticalCombo->currentIndex());

    if(laptopClosedBatteryNone->isChecked())
    {
        PowerDevilSettings::setBatLidAction(0);
    }
    else if(laptopClosedBatteryHibernate->isChecked())
    {
        PowerDevilSettings::setBatLidAction((int) S2Disk);
    }
    else if(laptopClosedBatterySuspend->isChecked())
    {
        PowerDevilSettings::setBatLidAction((int) S2Ram);
    }
    else if(laptopClosedBatteryShutdown->isChecked())
    {
        PowerDevilSettings::setBatLidAction((int) Shutdown);
    }
    else if(laptopClosedBatteryBlank->isChecked())
    {
        PowerDevilSettings::setBatLidAction((int) Lock);
    }
    if(laptopClosedACNone->isChecked())
    {
        PowerDevilSettings::setACLidAction(0);
    }
    else if(laptopClosedACHibernate->isChecked())
    {
        PowerDevilSettings::setACLidAction((int) S2Disk);
    }
    else if(laptopClosedACSuspend->isChecked())
    {
        PowerDevilSettings::setACLidAction((int) S2Ram);
    }
    else if(laptopClosedACShutdown->isChecked())
    {
        PowerDevilSettings::setACLidAction((int) Shutdown);
    }
    else if(laptopClosedACBlank->isChecked())
    {
        PowerDevilSettings::setACLidAction((int) Lock);
    }
}

void ConfigWidget::emitChanged()
{
    emit changed(true);
}

#include "ConfigWidget.moc"
