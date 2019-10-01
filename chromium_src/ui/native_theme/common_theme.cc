

#include "ui/native_theme/common_theme.h"

#define GetAuraColor GetAuraColor_ChromiumImpl
#include "../../../../ui/native_theme/common_theme.cc"
#undef GetAuraColor

namespace
{
  const SkColor kBraveBrandColor = SkColorSetRGB(0xff, 0x76, 0x54);
}  // namespace


namespace ui
{
  SkColor GetAuraColor(NativeTheme::ColorId color_id,
                     const NativeTheme* base_theme) {
    bool is_dark = base_theme->SystemDarkModeEnabled();
    switch (color_id) {
      // case NativeTheme::kColorId_LabelEnabledColor:
      //   return is_dark ? SK_ColorWHITE
      //                 : SkCoSkColorSetRGB(0x3b, 0x3e, 0x4f);
      case NativeTheme::kColorId_ButtonEnabledColor:
        return is_dark ? SK_ColorWHITE
                      : SkColorSetRGB(0x3b, 0x3e, 0x4f);
      case NativeTheme::kColorId_ButtonHoverColor:
        return kBraveBrandColor;
      case NativeTheme::kColorId_ButtonPressedShade:
        return SK_ColorTRANSPARENT;
      // case NativeTheme::kColorId_ButtonDisabledColor:
      //   return kDisabledTextColor;
      case NativeTheme::kColorId_ProminentButtonColor:
      case NativeTheme::kColorId_ProminentButtonFocusedColor:
        return kBraveBrandColor;
      case NativeTheme::kColorId_ProminentButtonDisabledColor:
        return gfx::kGoogleGrey800;
      case NativeTheme::kColorId_TextOnProminentButtonColor:
        return SK_ColorWHITE;
      case NativeTheme::kColorId_ButtonBorderColor:
        return SkColorSetRGB(0xc2, 0xc4, 0xcf);
      case NativeTheme::kColorId_LabelEnabledColor: {
        SkColor button = GetAuraColor(NativeTheme::kColorId_ButtonEnabledColor,
            base_theme);
        return button;
      }
      default:
        break;
    }
    return GetAuraColor_ChromiumImpl(color_id, base_theme);
  }

}  // namespace ui

