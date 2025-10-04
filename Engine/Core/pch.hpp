#pragma once

// Standard Library
#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <map>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <thread>
#include <utility>
#include <vector>

// Utility
#include "Utility/ToString.hpp"

// Recorder
#include "Recorder/Instrumentor/InstrumentationTimer.hpp"
#include "Recorder/Instrumentor/Instrumentor.hpp"
#include "Recorder/Logger/Logger.hpp"
#include "Recorder/Timer/Timer.hpp"

// Third Party
#include "Utility/Math.hpp"
#include "Utility/libtinyfiledialogs/tinyfiledialogs.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>