TEMPLATE = subdirs

SUBDIRS += \
    VES-Core \
    QVES-App \
    QVES-ModelDelegate

QVES-ModelDelegate.depends = VES-Core
QVES-App.depends = VES-Core
QVES-App.depends = QVES-ModelDelegate
