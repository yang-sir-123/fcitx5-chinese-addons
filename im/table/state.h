/*
 * SPDX-FileCopyrightText: 2017-2017 CSSlayer <wengxt@gmail.com>
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 *
 */
#ifndef _TABLE_STATE_H_
#define _TABLE_STATE_H_

#include "context.h"
#include "engine.h"
#include <fcitx/inputcontextproperty.h>

namespace fcitx {

enum class TableMode {
    Normal,
    ModifyDictionary,
    ForgetWord,
    Pinyin,
    LookupPinyin,
};

class EventSourceTime;

class TableState : public InputContextProperty {
public:
    TableState(InputContext *ic, TableEngine *engine)
        : ic_(ic), engine_(engine) {}

    InputContext *ic_;
    TableEngine *engine_;
    bool lastIsPunc_ = false;
    std::unique_ptr<EventSourceTime> cancelLastEvent_;

    TableContext *context(const InputMethodEntry *entry);
    void release();
    void reset(const InputMethodEntry *entry = nullptr);

    void keyEvent(const InputMethodEntry &entry, KeyEvent &event);

    void commitBuffer(bool commitCode, bool noRealCommit = false);
    void updateUI();
    void pushLastCommit(const std::string &lastSegment);

    void commitAfterSelect(int commitFrom);

    auto mode() const { return mode_; }

    void forgetCandidateWord(size_t idx);

private:
    bool handle2nd3rdCandidate(const TableConfig &config, KeyEvent &event);
    bool handleCandidateList(const TableConfig &config, KeyEvent &event);
    bool handleForgetWord(KeyEvent &event);
    bool handlePinyinMode(KeyEvent &event);
    bool handleLookupPinyinOrModifyDictionaryMode(KeyEvent &event);

    TableMode mode_ = TableMode::Normal;
    std::string pinyinModePrefix_;
    InputBuffer pinyinModeBuffer_{
        {InputBufferOption::AsciiOnly, InputBufferOption::FixedCursor}};
    size_t lookupPinyinIndex_ = 0;
    std::string lookupPinyinString_;
    std::string lastContext_;
    std::string lastCommit_;
    std::string lastSegment_;
    std::list<std::string> lastSingleCharCommit_;
    std::unique_ptr<TableContext> context_;

    int keyReleased_ = -1;
    int keyReleasedIndex_ = -2;
};
} // namespace fcitx

#endif // _TABLE_STATE_H_
