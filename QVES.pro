TEMPLATE = subdirs

SUBDIRS += \
    VES-Core \
    QVES-App

QVES-App.depends = VES-Core
