#include "ui/views/controls/button/md_text_button.h"

#include "ui/views/animation/ink_drop_mask.h"

#define Create Create_ChromiumImpl
#define CreateSecondaryUiBlueButton CreateSecondaryUiBlueButton_ChromiumImpl
#define CreateSecondaryUiButton CreateSecondaryUiButton_ChromiumImpl
#include "../../../../../ui/views/controls/button/md_text_button.cc"
#undef CreateSecondaryUiButton
#undef CreateSecondaryUiBlueButton
#undef Create

namespace views {

class BraveTextButton : public MdTextButton {
 public:
  using MdTextButton::MdTextButton;
  std::unique_ptr<views::InkDropMask> CreateInkDropMask() const override;
//  protected:
  // void OnBoundsChanged(const gfx::Rect& previous_bounds) override;
 private:
  DISALLOW_COPY_AND_ASSIGN(BraveTextButton);
};

// static
std::unique_ptr<LabelButton> MdTextButton::CreateSecondaryUiButton(
    ButtonListener* listener,
    const base::string16& text) {
  return MdTextButton::Create(listener, text, style::CONTEXT_BUTTON_MD);
}

// static
std::unique_ptr<LabelButton> MdTextButton::CreateSecondaryUiBlueButton(
    ButtonListener* listener,
    const base::string16& text) {
  auto md_button =
      MdTextButton::Create(listener, text, style::CONTEXT_BUTTON_MD);
  md_button->SetProminent(true);
  return md_button;
}

// static
std::unique_ptr<MdTextButton> MdTextButton::Create(ButtonListener* listener,
                                                   const base::string16& text,
                                                   int button_context) {
  auto button = base::WrapUnique<BraveTextButton>(
      new BraveTextButton(listener, button_context));
  button->SetText(text);
  button->SetFocusForPlatform();
  button->SetCornerRadius(20);
  return button;
}

std::unique_ptr<views::InkDropMask> BraveTextButton::CreateInkDropMask() const {
  return std::make_unique<RoundRectInkDropMask>(
      size(), GetInsets(), 20);
}

}  // namespace views
