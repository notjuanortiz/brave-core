#include "chrome/browser/ui/views/chrome_typography_provider.h"
#include "ui/gfx/color_palette.h"

namespace gfx {
  const SkColor kBraveWhite = SkColorSetRGB(0xff, 0xff, 0xff);
  const SkColor kBraveGrey800 = SkColorSetRGB(0x3b, 0x3e, 0x4f);
}

#define kGoogleGrey900 kBraveWhite
#define kGoogleBlue300 kBraveWhite
#define kGoogleBlue600 kBraveGrey800
#include "../../../../../chrome/browser/ui/views/chrome_typography_provider.cc"
#undef kGoogleGrey900
#undef kGoogleBlue300
#undef kGoogleBlue600

// SkColor ChromeTypographyProvider::GetColor(const views::View& view,
//                                            int context,
//                                            int style) const {
//   // For some colors this bypasses
// }