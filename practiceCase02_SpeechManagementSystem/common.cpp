#include "common.h"

ostream& operator<<(ostream& output, const _ContestantType& contestant) {
    // TODO: �ڴ˴����� return ���
    output << "name: " << right << setw(20) << fixed << contestant.name
           << "\tage: " << contestant.age << "\tid: " << contestant.id
           << " Preliminary: " << contestant.score.preliminaryScore
           << " Rematch: " << contestant.score.rematchScore
           << " Finals: " << contestant.score.finalsScore;
    return output;
}
