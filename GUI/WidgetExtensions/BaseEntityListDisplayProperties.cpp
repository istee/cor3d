#include "GUI/WidgetExtensions/BaseEntityDisplayProperties.h"

bool BaseEntityDisplayProperties::isEdited() const
{
    return _isEdited;
}

void BaseEntityDisplayProperties::setEdited(bool isEdited)
{
    _isEdited = isEdited;
}

bool BaseEntityDisplayProperties::isExtended() const
{
    return _isExtended;
}

void BaseEntityDisplayProperties::setExtended(bool isExtended)
{
    _isExtended = isExtended;
}
