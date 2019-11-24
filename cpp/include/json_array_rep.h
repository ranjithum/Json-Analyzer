#pragma once

//! This class represents a Json Array
//! In case of for condition this would represent array object
class JsonArrayRep {
public:
    //! Method used for incrementing the index which would eventually
    //! represent the next subsequent value
    virtual int GetArraySize() = 0;

    virtual JsonArrayRep& Clone() = 0;

    virtual ~JsonArrayRep() = default;
};
