#include "common.h"

ostream& operator<<(ostream& output, const _ContestantType& contestant) {
    // TODO: 在此处插入 return 语句
    output << "name: " << right << setw(20) << fixed << contestant.name
           << "\tage: " << contestant.age << "\tid: " << contestant.id
           << " Preliminary: " << contestant.score.preliminaryScore
           << " Rematch: " << contestant.score.rematchScore
           << " Finals: " << contestant.score.finalsScore;
    return output;
}
