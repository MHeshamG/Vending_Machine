# Color variables for logs
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Function to display logs in green color with a checkmark
green_log() {
    echo -e "${GREEN}✔ $1${NC}"
}

# Function to display logs in yellow color
yellow_log() {
    echo -e "${YELLOW}$1${NC}"
}

# Function to display logs in red color and exit
red_log_and_exit() {
    echo -e "${RED}❌ $1${NC}"
    exit 1
}