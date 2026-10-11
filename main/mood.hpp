#pragma once
#include <cstdint>

class Mood{
    public:
        virtual ~Mood()=default;

        virtual const char* name() const =0;
        virtual uint32_t blinkInterval() const=0;
        virtual uint32_t blinkDuration() const=0;
        virtual float pupilRange() const=0;
        virtual float pupilbias() const=0;
};

class Idlemood : public Mood{
    public:
        const char* name() const override;
        uint32_t blinkInterval() const override;
        uint32_t blinkDuration() const override;
        float pupilRange() const override;
        float pupilbias() const override;
};

class Happymood : public Mood{
    public:
        const char* name() const override;
        uint32_t blinkInterval() const override;
        uint32_t blinkDuration() const override;
        float pupilRange() const override;
        float pupilbias() const override;
};

class Suprisedmood : public Mood{
    public:
        const char* name() const override;
        uint32_t blinkInterval() const override;
        uint32_t blinkDuration() const override;
        float pupilRange() const override;
        float pupilbias() const override;
};

class Sleepymood : public Mood{
    public:
        const char* name() const override;
        uint32_t blinkInterval() const override;
        uint32_t blinkDuration() const override;
        float pupilRange() const override;
        float pupilbias() const override;
};

