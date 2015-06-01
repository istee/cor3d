#pragma once

class BaseEntityDisplayProperties
{
private:
    bool    _isExtended;
    bool    _isEdited;

public:
    bool isEdited() const;
    void setEdited(bool);
    bool isExtended() const;
    void setExtended(bool);
};
