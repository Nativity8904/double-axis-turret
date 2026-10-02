#ifndef STATS_H
#define STATS_H

constexpr int SAMPLE_COUNT = 128;

template<typename T>
class Stats {
    T rawSamples[SAMPLE_COUNT];
    int rawSamplesIndex;
    bool didRawSamplesCycle;

public:
    Stats();

    void update(T newSample);
    float getMean() const;
    float getStd() const;
};

template<typename T>
Stats<T>::Stats() : rawSamples{}, rawSamplesIndex(0), didRawSamplesCycle(false) {}

template<typename T>
void Stats<T>::update(T newSample) {
    rawSamples[rawSamplesIndex] = newSample;

    rawSamplesIndex = (rawSamplesIndex + 1) % SAMPLE_COUNT;

    if (!didRawSamplesCycle) {
        if (rawSamplesIndex == 0) { didRawSamplesCycle = true; }
    }
}

template<typename T>
float Stats<T>::getMean() const {
    int loopCount = (!didRawSamplesCycle) ? rawSamplesIndex : SAMPLE_COUNT;
    if (loopCount == 0) { return 0.0f; }

    float total{0.0f};

    for (int i = 0; i < loopCount; i++) {
        total += static_cast<float>(rawSamples[i]);
    }

    return total / loopCount;
}

template<typename T>
float Stats<T>::getStd() const {
    int loopCount = (!didRawSamplesCycle) ? rawSamplesIndex : SAMPLE_COUNT;
    if (loopCount == 0) { return 0.0f; }

    float mean = this->getMean();

    float squaredDifferenceSum = 0.0f;
    for (int i = 0; i < loopCount; i++) {
        squaredDifferenceSum += (static_cast<float>(rawSamples[i]) - mean) * (static_cast<float>(rawSamples[i]) - mean);
    }

    float variance = squaredDifferenceSum / loopCount;
    return sqrt(variance);
}

#endif // STATS_H
