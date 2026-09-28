#ifndef STATS_H
#define STATS_H

template<typename T>
class Stats {
    T rawSamples[128];

public:
    Stats();

    void update(T newSample);
    float getMean() const;
    float getStd() const;
};

template<typename T>
Stats<T>::Stats() : rawSamples{} {}

template<typename T>
void Stats<T>::update(T newSample) {
    for (int i = 126; i >=0; i--) {
        rawSamples[i + 1] = rawSamples[i];
    }
    rawSamples[0] = newSample;
}

template<typename T>
float Stats<T>::getMean() const {
    float total{0.0f};
    for (int i = 0; i < 128; i++) {
        total += static_cast<float>(rawSamples[i]);
    }
    return total / 128.0f;
}

template<typename T>
float Stats<T>::getStd() const {
    float mean = this->getMean();

    float squaredDifferenceSum = 0.0f;
    for (int i = 0; i < 128; i++) {
        squaredDifferenceSum += (static_cast<float>(rawSamples[i]) - mean) * (static_cast<float>(rawSamples[i]) - mean);
    }

    float variance = squaredDifferenceSum / 128.0f;
    return sqrt(squaredDifferenceSum);
}

#endif // STATS_H
